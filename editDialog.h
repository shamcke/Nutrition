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
#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include "mapOfIngredients.h"
#include "ui_editDialog.h"
#include <QMetaProperty>
#include <QVariant>

using std::shared_ptr;
using std::vector;

class EditDialog : public QDialog {
    Q_OBJECT

public:
    explicit EditDialog(const shared_ptr<const vector<QMetaProperty>>& props,
        const shared_ptr<MapOfIngredients>& map, const QString& name, QWidget* parent = nullptr);

signals:
    void ingredientChanged(const QString&);

private slots:
    void on_buttonCancel_clicked();
    void on_buttonOK_clicked();

private:
    Ui::EditDialog ui;
    const shared_ptr<const vector<QMetaProperty>> m_ingredientProps;
    const shared_ptr<MapOfIngredients> m_mapOfIngredients;
    shared_ptr<Ingredient> m_ingredient;
};

#endif // EDITDIALOG_H
