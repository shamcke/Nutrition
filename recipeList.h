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
#ifndef RECIPELIST_H
#define RECIPELIST_H

#include "measuredIngredient.h"
#include <QMap>

using std::shared_ptr;

class RecipeList : public QObject {
    Q_OBJECT

public:
    explicit RecipeList(QObject* parent = nullptr);
    void insert(const QString& name, const shared_ptr<MeasuredIngredient>& ing);
    void insert(const QString& name, const shared_ptr<Ingredient>& ing);
    void edit(const QString& name, uint16_t quantity = 0);
    const QMap<const QString, shared_ptr<MeasuredIngredient>>& map() const;

public slots:
    void remove(const QString& name);

signals:
    void ingredientAdded(const shared_ptr<const MeasuredIngredient>&);
    void quantityChanged(const QString& name, uint16_t quantity = 0);
    void ingredientRemoved(const QString& name);

private:
    QMap<const QString, shared_ptr<MeasuredIngredient>> m_map;
};

inline RecipeList::RecipeList(QObject* parent)
    : QObject(parent)
{
}

inline const QMap<const QString, shared_ptr<MeasuredIngredient>>& RecipeList::map() const
{
    return m_map;
}

#endif // RECIPELIST_H
