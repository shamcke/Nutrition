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
#ifndef MAPOFINGREDIENTS_H
#define MAPOFINGREDIENTS_H

#include "ingredient.h"
#include <QMap>

using std::shared_ptr;

class MapOfIngredients : public QObject {
    Q_OBJECT

public:
    explicit MapOfIngredients(QObject* parent = nullptr);
    void insert(const QString& name, const shared_ptr<Ingredient>& ing);
    void edit(const QString& name, const shared_ptr<Ingredient>& ing);
    const QMap<const QString, shared_ptr<Ingredient>>& map() const;

signals:
    void ingredientAdded(const shared_ptr<const Ingredient>&);
    void ingredientChanged(const QString& name);

private:
    QMap<const QString, shared_ptr<Ingredient>> m_map;
};

inline MapOfIngredients::MapOfIngredients(QObject* parent)
    : QObject(parent)
{
}

inline const QMap<const QString, shared_ptr<Ingredient>>& MapOfIngredients::map() const
{
    return m_map;
}

#endif // MAPOFINGREDIENTS_H
