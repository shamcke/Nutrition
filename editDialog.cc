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
#include "editDialog.h"
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

EditDialog::EditDialog(const shared_ptr<const vector<QMetaProperty>>& props,
    const shared_ptr<MapOfIngredients>& map, const QString& name, QWidget* parent)
    : QDialog(parent)
    , m_ingredientProps(props)
    , m_mapOfIngredients(map)
    , m_ingredient { m_mapOfIngredients->map().value(name) }
{
    ui.setupUi(this);
    QLabel* label = new QLabel(this);
    label->setObjectName("labelName");
    label->setText("Name");
    ui.formLayout->setWidget(0, QFormLayout::LabelRole, label);
    QLineEdit* lineEdit = new QLineEdit(this);
    lineEdit->setObjectName("lineEditName");
    lineEdit->setText(name);
    lineEdit->setEnabled(false);
    ui.formLayout->setWidget(0, QFormLayout::FieldRole, lineEdit);
    for (size_t i = 1; i < m_ingredientProps->size(); i++) {
        QString attribute = m_ingredientProps->at(i).name();
        QLabel* label = new QLabel(this);
        label->setObjectName("label" + attribute.first(1).toUpper()
            + attribute.sliced(1, attribute.size() - 1));
        label->setText(attribute.first(1).toUpper() + attribute.sliced(1, attribute.size() - 1));
        ui.formLayout->setWidget(i, QFormLayout::LabelRole, label);
        QLineEdit* lineEdit = new QLineEdit(this);
        lineEdit->setObjectName("lineEdit" + attribute.first(1).toUpper()
            + attribute.sliced(1, attribute.size() - 1));
        ui.formLayout->setWidget(i, QFormLayout::FieldRole, lineEdit);
        QVariant prop = m_ingredient->property(attribute.toStdString().c_str());
        lineEdit->setText(QString::number(prop.value<float>()));
    }
}

void EditDialog::on_buttonCancel_clicked()
{
    close();
}

void EditDialog::on_buttonOK_clicked()
{
    shared_ptr<Ingredient> ing = std::make_shared<Ingredient>(m_ingredient->name());
    for (int i = 1; i < ui.formLayout->rowCount(); i++) {
        const char* attribute = m_ingredientProps->at(i).name();
        QLineEdit* value_edit = static_cast<QLineEdit*>(
            ui.formLayout->itemAt(i, QFormLayout::FieldRole)->widget());
        ing->setProperty(attribute, value_edit->text().toFloat());
    }
    m_mapOfIngredients->edit(ing->name(), ing);
}
