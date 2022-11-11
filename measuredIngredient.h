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
#ifndef MEASUREDINGREDIENT_H
#define MEASUREDINGREDIENT_H

#include "ingredient.h"
#include <stdexcept>

class MeasuredIngredient {
public:
    MeasuredIngredient();
    MeasuredIngredient(const std::shared_ptr<Ingredient>&);
    const std::shared_ptr<Ingredient>& getIngredient() const;
    uint16_t getQuantity() const;
    void setQuantity(uint16_t newQuantity);
    void setQuantity(QString s);

private:
    const std::shared_ptr<Ingredient> ingredient;
    uint16_t quantity { 0 };
};

inline MeasuredIngredient::MeasuredIngredient(const std::shared_ptr<Ingredient>& _ingredient)
    : ingredient { _ingredient }
{
}

inline const std::shared_ptr<Ingredient>& MeasuredIngredient::getIngredient() const
{
    return ingredient;
}

inline uint16_t MeasuredIngredient::getQuantity() const
{
    return quantity;
}

inline void MeasuredIngredient::setQuantity(uint16_t newQuantity)
{
    quantity = newQuantity;
}

#endif // MEASUREDINGREDIENT_H
