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
#include "mapOfIngredients.h"

void MapOfIngredients::insert(const QString& name, const std::shared_ptr<Ingredient>& ing)
{
    m_map.insert(name, ing);
    emit ingredientAdded(ing);
}

void MapOfIngredients::edit(const QString& name, const shared_ptr<Ingredient>& ing)
{
    *m_map.value(name) = *ing;
    emit ingredientChanged(name);
}

void MapOfIngredients::remove(const QString& name)
{
    m_map.remove(name);
    emit ingredientRemoved(name);
}
