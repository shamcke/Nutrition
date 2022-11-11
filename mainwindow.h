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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "editDialog.h"
#include "mapOfIngredients.h"
#include "measuredIngredient.h"
#include "newIngredientDialog.h"
#include "recipeList.h"
#include "ui_mainwindow.h"

#include <QMainWindow>
#include <QMetaObject>
#include <QMetaProperty>
#include <QStringList>
#include <iostream>

using std::shared_ptr;
using std::vector;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

signals:

private slots:
    void on_listOfIngredients_itemActivated(QTableWidgetItem* item);
    void on_listOfMeal_itemChanged(QTableWidgetItem* item);
    void on_listOfMeal_itemActivated(QTableWidgetItem* item);
    void on_addButton_clicked();
    void on_editButton_clicked();
    void on_deleteButton_clicked();
    void on_selectedAtTop_clicked();
    void addIngredient(const shared_ptr<const Ingredient>& ing);
    void changeIngredient(const QString& name);
    void removeIngredient(const QString& name);
    void addIngredientToMeal(const shared_ptr<const MeasuredIngredient>& ing);
    void removeIngredientFromMeal(const QString& name);
    void updateNutrition();

private:
    Ui::MainWindow ui;
    shared_ptr<NewIngredientDialog> m_newDialog = nullptr;
    shared_ptr<EditDialog> m_editDialog = nullptr;
    shared_ptr<vector<QMetaProperty>> m_ingredientProps
        = std::make_shared<vector<QMetaProperty>>();
    shared_ptr<MapOfIngredients> m_mapOfIngredients = std::make_shared<MapOfIngredients>();
    shared_ptr<RecipeList> m_recipeList = std::make_shared<RecipeList>();
};

#endif // MAINWINDOW_H
