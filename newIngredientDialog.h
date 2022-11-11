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
#ifndef NEWINGREDIENTDIALOG_H
#define NEWINGREDIENTDIALOG_H

#include "ingredient.h"
#include "mapOfIngredients.h"
#include "ui_newIngredientDialog.h"
#include <QMetaObject>
#include <QMetaProperty>

using std::shared_ptr;
using std::vector;

class NewIngredientDialog : public QDialog {
    Q_OBJECT

public:
    explicit NewIngredientDialog(const shared_ptr<vector<QMetaProperty>>&, const shared_ptr<MapOfIngredients>&,
        QWidget* parent = nullptr);

signals:

private slots:
    void on_buttonOK_clicked();
    void on_buttonCancel_clicked();
    void on_lineEditName_textChanged(const QString& arg1);

private:
    Ui::NewIngredientDialog ui;
    const shared_ptr<vector<QMetaProperty>> m_ingredientProps;
    const shared_ptr<MapOfIngredients> m_mapOfIngredients = std::make_shared<MapOfIngredients>();
};

#endif // NEWINGREDIENTDIALOG_H
