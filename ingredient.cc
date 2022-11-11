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
#include "ingredient.h"
#include <QLocale>

using std::shared_ptr;
using std::string;
using std::vector;

Ingredient::Ingredient(const QString& name, QObject* parent)
    : QObject(parent)
    , m_name(name)
{
}

Ingredient::Ingredient(const char* name, QObject* parent)
    : Ingredient(QString(name), parent)
{
}

Ingredient& Ingredient::operator=(const Ingredient& other)
{
    setNutrition(other.m_energy, other.m_fat, other.m_saturated, other.m_carbonhydrates,
        other.m_sugars, other.m_fiber, other.m_protein, other.m_salt);
    return *this;
}

const QString& Ingredient::name() const
{
    return m_name;
}

unsigned short Ingredient::energy() const
{
    return m_energy;
}

void Ingredient::setEnergy(unsigned short newEnergy)
{
    assert(newEnergy >= 0);
    m_energy = newEnergy;
}

float Ingredient::fat() const
{
    return m_fat;
}

void Ingredient::setFat(float newFat)
{
    assert(newFat >= 0);
    m_fat = newFat;
}

float Ingredient::saturated() const
{
    return m_saturated;
}

void Ingredient::setSaturated(float newSaturated)
{
    assert(newSaturated >= 0);
    m_saturated = newSaturated;
}

float Ingredient::carbonhydrates() const
{
    return m_carbonhydrates;
}

void Ingredient::setCarbonhydrates(float newCarbonhydrates)
{
    assert(newCarbonhydrates >= 0);
    m_carbonhydrates = newCarbonhydrates;
}

float Ingredient::sugars() const
{
    return m_sugars;
}

void Ingredient::setSugars(float newSugars)
{
    assert(newSugars >= 0);
    m_sugars = newSugars;
}

float Ingredient::fiber() const
{
    return m_fiber;
}

void Ingredient::setFiber(float newFiber)
{
    assert(newFiber >= 0);
    m_fiber = newFiber;
}

float Ingredient::protein() const
{
    return m_protein;
}

void Ingredient::setProtein(float newProtein)
{
    assert(newProtein >= 0);
    m_protein = newProtein;
}

float Ingredient::salt() const
{
    return m_salt;
}

void Ingredient::setSalt(float newSalt)
{
    assert(newSalt >= 0);
    m_salt = newSalt;
}

void Ingredient::setNutrition(unsigned short energy, float fat, float saturated,
    float carbonhydrates, float sugars, float fiber, float protein, float salt)
{
    setEnergy(energy);
    setFat(fat);
    setSaturated(saturated);
    setCarbonhydrates(carbonhydrates);
    setSugars(sugars);
    setFiber(fiber);
    setProtein(protein);
    setSalt(salt);
}
