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
#include "recipeList.h"

void RecipeList::insert(const QString& name, const shared_ptr<MeasuredIngredient>& ing)
{
    m_map.insert(name, ing);
    emit ingredientAdded(ing);
}

void RecipeList::insert(const QString& name, const shared_ptr<Ingredient>& ing)
{
    shared_ptr<MeasuredIngredient> measured = std::make_shared<MeasuredIngredient>(ing);
    insert(name, measured);
}

void RecipeList::edit(const QString& name, uint16_t quantity)
{
    if (m_map.value(name)->getQuantity() == quantity)
        return;
    m_map.value(name)->setQuantity(quantity);
    emit quantityChanged(name, quantity);
}

void RecipeList::remove(const QString& name)
{
    if (m_map.remove(name))
        emit ingredientRemoved(name);
}
