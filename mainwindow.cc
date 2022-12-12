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
#include "mainwindow.h"
#include "numberItem.h"
#include <QLocale>
#include <QMessageBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

using std::cout;
using std::endl;
using std::string;

QTableWidgetItem* zeroColumn(QTableWidgetItem* item)
{
    return item->tableWidget()->item(item->row(), 0);
}

QTableWidgetItem* neighborItem(QTableWidgetItem* item, int i = 0)
{
    return item->tableWidget()->item(item->row(), i);
}

QString floatToString(float f)
{ // Converts a float to a QString with exactly 1 digit after the point
    int g = round(f * 10);
    if (g % 10 == 0) {
        return QString::number(g / 10).append(".0");
    }
    return QString::number(g / 10.0);
}

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    shared_ptr<Ingredient> tofu = std::make_shared<Ingredient>("Tofu");
    tofu->setEnergy(119);
    tofu->setFat(6.7);
    tofu->setSaturated(1.2);
    tofu->setCarbonhydrates(1.3);
    tofu->setSugars(0.5);
    tofu->setProtein(13);
    shared_ptr<Ingredient> wheat_flour = std::make_shared<Ingredient>("Weizenmehl");
    wheat_flour->setNutrition(349, 1.1, 0.2, 72.0, 1.1, 4.3, 11.0, 0.0);
    shared_ptr<Ingredient> soy_sauce = std::make_shared<Ingredient>("Soja-Sauce");
    soy_sauce->setNutrition(87, 0, 0, 9.9, 2.4, 1.8, 11, 15.9);
    const QMetaObject* meta = tofu->metaObject();
    for (int i = meta->propertyOffset(); i < meta->propertyCount(); ++i)
        m_ingredientProps->push_back(meta->property(i));
    ui.setupUi(this);
    // Set up the list of ingredients
    ui.listOfIngredients->setColumnCount(m_ingredientProps->size());
    ui.listOfIngredients->setRowCount(m_mapOfIngredients->map().size());
    for (int col = 0; col < ui.listOfIngredients->columnCount(); col++) {
        ui.listOfIngredients->setHorizontalHeaderItem(col, new QTableWidgetItem);
        ui.listOfIngredients->horizontalHeaderItem(col)->setText(m_ingredientProps->at(col).name());
    }
    QObject::connect(
        m_mapOfIngredients.get(),
        SIGNAL(ingredientAdded(const shared_ptr<const Ingredient>&)),
        this,
        SLOT(addIngredient(const shared_ptr<const Ingredient>&)));
    m_mapOfIngredients->insert(tofu->name(), tofu);
    m_mapOfIngredients->insert(wheat_flour->name(), wheat_flour);
    m_mapOfIngredients->insert(soy_sauce->name(), soy_sauce);
    QObject::connect(
        m_recipeList.get(),
        SIGNAL(ingredientAdded(const shared_ptr<const MeasuredIngredient>&)),
        this,
        SLOT(addIngredientToMeal(const shared_ptr<const MeasuredIngredient>&)));
    ui.listOfIngredients->resizeColumnsToContents();
    // Construct the nutrition table for the meal
    for (size_t i = 1; i < m_ingredientProps->size(); i++) {
        const QString& attribute = m_ingredientProps->at(i).name();
        QLabel* name = new QLabel(ui.centralwidget);
        name->setObjectName(attribute);
        name->setText(attribute);
        ui.nutritionTable->setWidget(i - 1, QFormLayout::LabelRole, name);
        QLabel* value = new QLabel(ui.centralwidget);
        value->setObjectName(attribute);
        value->setText("0");
        value->setAlignment(Qt::AlignRight);
        ui.nutritionTable->setWidget(i - 1, QFormLayout::FieldRole, value);
    }
    QObject::connect(
        m_mapOfIngredients.get(),
        SIGNAL(ingredientChanged(const QString&)),
        this,
        SLOT(updateNutrition()));
    QObject::connect(
        m_mapOfIngredients.get(),
        SIGNAL(ingredientRemoved(const QString&)),
        this,
        SLOT(removeIngredient(const QString&)));
    QObject::connect(
        m_mapOfIngredients.get(),
        SIGNAL(ingredientRemoved(const QString&)),
        m_recipeList.get(),
        SLOT(remove(const QString&)));
    QObject::connect(
        m_recipeList.get(),
        SIGNAL(quantityChanged(const QString&, uint16_t)),
        m_recipeList.get(),
        SLOT(updateWeight()));
    QObject::connect(
        m_recipeList.get(),
        SIGNAL(quantityChanged(const QString&, uint16_t)),
        this,
        SLOT(updateNutrition()));
    QObject::connect(
        m_recipeList.get(),
        SIGNAL(ingredientRemoved(const QString&)),
        m_recipeList.get(),
        SIGNAL(quantityChanged(const QString&)));
    QObject::connect(
        m_recipeList.get(),
        SIGNAL(ingredientRemoved(const QString&)),
        this,
        SLOT(removeIngredientFromMeal(const QString&)));
}

MainWindow::~MainWindow()
{
}

void MainWindow::on_listOfIngredients_itemActivated(QTableWidgetItem* active_item)
{
    QString ingredient_name = zeroColumn(active_item)->text();
    if (m_recipeList->map().contains(ingredient_name))
        return;
    for (int i = 0; i < ui.listOfIngredients->columnCount(); i++) {
        neighborItem(active_item, i)->setBackground(QBrush(QColor(255, 240, 240, 255)));
    }
    m_recipeList->insert(ingredient_name, m_mapOfIngredients->map().value(ingredient_name));
}

void MainWindow::on_listOfMeal_itemChanged(QTableWidgetItem* item)
{
    if (item->column() != 1)
        return;
    bool* ok = new bool;
    uint16_t quantity = item->text().toUInt(ok);
    if (!*ok) {
        item->setText("0");
        dynamic_cast<NumberItem*>(item)->setValue(0);
        return;
    }
    m_recipeList->edit(zeroColumn(item)->text(), quantity);
    dynamic_cast<NumberItem*>(item)->setValue(quantity);
}

void MainWindow::on_listOfMeal_itemActivated(QTableWidgetItem* item)
{
    if (item->column() != 0)
        return;
    m_recipeList->remove(zeroColumn(item)->text());
}

void MainWindow::on_addButton_clicked()
{

    m_newDialog = std::make_shared<NewIngredientDialog>(m_ingredientProps, m_mapOfIngredients, this);
    m_newDialog->setModal(true);
    m_newDialog->open();
}

void MainWindow::on_editButton_clicked()
{
    QTableWidgetItem* current = ui.listOfIngredients->currentItem();
    if (!current)
        return;
    QString name = zeroColumn(current)->text();
    m_editDialog = std::make_shared<EditDialog>(m_ingredientProps, m_mapOfIngredients, name, this);
    QObject::connect(m_mapOfIngredients.get(), SIGNAL(ingredientChanged(const QString&)),
        this, SLOT(changeIngredient(const QString&)));
    m_editDialog->setModal(true);
    m_editDialog->open();
}

void MainWindow::on_deleteButton_clicked()
{
    QTableWidgetItem* current = ui.listOfIngredients->currentItem();
    if (!current)
        return;
    QString name = zeroColumn(current)->text();
    if (QMessageBox::question(this, "Delete", "Delete ingredient " + name + "?") == QMessageBox::No)
        return;
    m_mapOfIngredients->remove(name);
}

void MainWindow::on_onTop_stateChanged(int arg1)
{
    if (arg1 == 2) {
        ui.listOfIngredients->setSortingEnabled(false);
        int insert_index = 0;
        for (int i = 0; i < ui.listOfIngredients->rowCount(); i++) {
            if (m_recipeList->map().contains(ui.listOfIngredients->item(i, 0)->text())) {
                ui.listOfIngredients->insertRow(insert_index);
                for (int j = 0; j < ui.listOfIngredients->columnCount(); j++) {
                    QTableWidgetItem* newItem;
                    QTableWidgetItem* source = ui.listOfIngredients->item(i + 1, j);
                    NumberItem* source_as_number_item = dynamic_cast<NumberItem*>(source);
                    if (source_as_number_item) {
                        newItem = new NumberItem(*source_as_number_item);
                    } else {
                        newItem = new QTableWidgetItem(*source);
                    }
                    ui.listOfIngredients->setItem(insert_index, j, newItem);
                }
                insert_index++;
                ui.listOfIngredients->removeRow(i + 1);
            }
        }
    } else if (arg1 != 2) {
        ui.listOfIngredients->setSortingEnabled(true);
    }
}

void MainWindow::on_checkBoxRelative_stateChanged()
{
    updateNutrition();
}

void MainWindow::addIngredient(const shared_ptr<const Ingredient>& ing)
{
    int rows = ui.listOfIngredients->rowCount();
    ui.listOfIngredients->insertRow(rows);
    for (int col = 0; col < ui.listOfIngredients->columnCount(); col++) {
        QTableWidgetItem* item;
        QVariant prop = ing->property(m_ingredientProps->at(col).name());
        int type = prop.userType();
        if (type == QMetaType::Float || type == QMetaType::Double || type == QMetaType::UShort) {
            item = new NumberItem;
            dynamic_cast<NumberItem*>(item)->setValue(prop.toFloat());
            if (type == QMetaType::UShort) {
                item->setText(prop.toString());
            } else {
                item->setText(floatToString(prop.toFloat()));
            }
            item->setTextAlignment(0x0082);
        } else {
            item = new QTableWidgetItem;
            item->setText(prop.toString());
        }
        item->setFlags(Qt::ItemIsEnabled);
        ui.listOfIngredients->setItem(rows, col, item);
    }
}

void MainWindow::changeIngredient(const QString& name)
{
    const shared_ptr<const Ingredient> ing = m_mapOfIngredients->map().value(name);
    QList<QTableWidgetItem*> list = ui.listOfIngredients->findItems(name, Qt::MatchExactly);
    if (list.isEmpty())
        return;
    QTableWidgetItem* ingredient_in_list = list.at(0);
    for (int col = 0; col < ui.listOfIngredients->columnCount(); col++) {
        QTableWidgetItem* item = neighborItem(ingredient_in_list, col);
        QVariant prop = ing->property(m_ingredientProps->at(col).name());
        if (prop.userType() == QMetaType::Float || prop.userType() == QMetaType::Double)
            item->setText(floatToString(prop.toFloat()));
        else
            item->setText(prop.toString());
    }
}

void MainWindow::removeIngredient(const QString& name)
{
    QList<QTableWidgetItem*> list = ui.listOfIngredients->findItems(name, Qt::MatchExactly);
    if (list.isEmpty())
        return;
    ui.listOfIngredients->removeRow(list.at(0)->row());
}

void MainWindow::addIngredientToMeal(const shared_ptr<const MeasuredIngredient>& ing)
{
    QTableWidgetItem* added_ingredient = new QTableWidgetItem();
    added_ingredient->setFlags(Qt::ItemIsEnabled);
    added_ingredient->setText(ing->getIngredient()->name());
    ui.listOfMeal->insertRow(0);
    ui.listOfMeal->setItem(0, 0, added_ingredient);
    QTableWidgetItem* quantity = new NumberItem();
    quantity->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable);
    quantity->setTextAlignment(0x0082);
    quantity->setText(QString::number(ing->getQuantity()));
    dynamic_cast<NumberItem*>(quantity)->setValue(ing->getQuantity());
    ui.listOfMeal->setItem(0, 1, quantity);
}

void MainWindow::removeIngredientFromMeal(const QString& name)
{
    QList<QTableWidgetItem*> list = ui.listOfMeal->findItems(name, Qt::MatchExactly);
    if (list.isEmpty())
        return;
    ui.listOfMeal->removeRow(list.at(0)->row());
    list = ui.listOfIngredients->findItems(name, Qt::MatchExactly);
    if (list.isEmpty())
        return;
    QTableWidgetItem* ing = list.at(0);
    for (int i = 0; i < ui.listOfIngredients->columnCount(); i++) {
        neighborItem(ing, i)->setBackground(QBrush(Qt::NoBrush));
    }
}

void MainWindow::updateNutrition()
{
    for (size_t i = 1; i < m_ingredientProps->size(); i++) {
        const char* attribute = m_ingredientProps->at(i).name();
        QLabel* value = static_cast<QLabel*>(
            ui.nutritionTable->itemAt(i - 1, QFormLayout::FieldRole)->widget());
        float total = 0;
        for (const shared_ptr<MeasuredIngredient>& ing : m_recipeList->map()) {
            uint16_t quantity = ing->getQuantity();
            QVariant nutrient = ing->getIngredient()->property(attribute);
            total += quantity * nutrient.value<float>() / 100;
        }
        if (ui.checkBoxRelative->isChecked()) {
            total = total * 100 / m_recipeList->weight();
        }
        value->setText(floatToString(total));
    }
    ui.labelWeight->setText("Total weight: " + QString::number(m_recipeList->weight()));
}
