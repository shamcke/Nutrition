/*
 * Nutrition - Create a recipe from a list of ingredients and see its nutrition
 * Copyright (C) 2022 Stefan Hamcke <s.hamcke@posteo.de>

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include "newIngredientDialog.h"
#include <QMessageBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

NewIngredientDialog::NewIngredientDialog(const std::shared_ptr<std::vector<QMetaProperty>>& props, const shared_ptr<MapOfIngredients>& map,
    QWidget* parent)
    : QDialog(parent)
    , m_ingredientProps(props)
    , m_mapOfIngredients(map)
{
    ui.setupUi(this);
    QLineEdit* previous = ui.lineEditName;
    for (size_t i = 1; i < m_ingredientProps->size(); i++) {
        QString attribute = m_ingredientProps->at(i).name();
        QLabel* label = new QLabel(this);
        label->setObjectName("label" + attribute.first(1).toUpper() + attribute.sliced(1, attribute.size() - 1));
        label->setText(attribute);
        ui.formLayout->setWidget(i, QFormLayout::LabelRole, label);
        QLineEdit* lineEdit = new QLineEdit(this);
        lineEdit->setObjectName("lineEdit" + attribute.first(1).toUpper() + attribute.sliced(1, attribute.size() - 1));
        ui.formLayout->setWidget(i, QFormLayout::FieldRole, lineEdit);
        QWidget::setTabOrder(previous, lineEdit);
        previous = lineEdit;
    }
    QWidget::setTabOrder(previous, ui.buttonCancel);
}

void NewIngredientDialog::on_buttonOK_clicked()
{
    QLineEdit* name_edit = static_cast<QLineEdit*>(
        ui.formLayout->itemAt(0, QFormLayout::FieldRole)->widget());
    QString name = name_edit->text().simplified();
    shared_ptr<Ingredient> ing = std::make_shared<Ingredient>(name);
    for (int i = 1; i < ui.formLayout->rowCount(); i++) {
        const char* attribute = m_ingredientProps->at(i).name();
        QLineEdit* value_edit = static_cast<QLineEdit*>(
            ui.formLayout->itemAt(i, QFormLayout::FieldRole)->widget());
        ing->setProperty(attribute, value_edit->text().toFloat());
    }
    m_mapOfIngredients->insert(name, ing);
    close();
}

void NewIngredientDialog::on_buttonCancel_clicked()
{
    close();
}

void NewIngredientDialog::on_lineEditName_textChanged(const QString& arg1)
{
    QString name = arg1.simplified();
    ui.labelExists->clear();
    ui.buttonOK->setEnabled(true);
    if (m_mapOfIngredients->map().contains(name)) {
        ui.labelExists->setText("Ingredient with that name already exists.");
        ui.buttonOK->setEnabled(false);
    } else if (name.isEmpty()) {
        ui.labelExists->setText("Please enter a valid name.");
        ui.buttonOK->setEnabled(false);
    }
}
