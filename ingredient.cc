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
    m_energy = newEnergy;
}

double Ingredient::fat() const
{
    return m_fat;
}

void Ingredient::setFat(double newFat)
{
    if (newFat < 0 || newFat > 100) {
        m_valid = false;
    }
    m_fat = newFat;
}

double Ingredient::saturated() const
{
    return m_saturated;
}

void Ingredient::setSaturated(double newSaturated)
{
    if (newSaturated < 0 || newSaturated > 100) {
        m_valid = false;
    }
    m_saturated = newSaturated;
}

double Ingredient::carbonhydrates() const
{
    return m_carbonhydrates;
}

void Ingredient::setCarbonhydrates(double newCarbonhydrates)
{
    if (newCarbonhydrates < 0 || newCarbonhydrates > 100) {
        m_valid = false;
    }
    m_carbonhydrates = newCarbonhydrates;
}

double Ingredient::sugars() const
{
    return m_sugars;
}

void Ingredient::setSugars(double newSugars)
{
    if (newSugars < 0 || newSugars > 100) {
        m_valid = false;
    }
    m_sugars = newSugars;
}

double Ingredient::fiber() const
{
    return m_fiber;
}

void Ingredient::setFiber(double newFiber)
{
    if (newFiber < 0 || newFiber > 100) {
        m_valid = false;
    }
    m_fiber = newFiber;
}

double Ingredient::protein() const
{
    return m_protein;
}

void Ingredient::setProtein(double newProtein)
{
    if (newProtein < 0 || newProtein > 100) {
        m_valid = false;
    }
    m_protein = newProtein;
}

double Ingredient::salt() const
{
    return m_salt;
}

void Ingredient::setSalt(double newSalt)
{
    if (newSalt < 0 || newSalt > 100) {
        m_valid = false;
    }
    m_salt = newSalt;
}

void Ingredient::setNutrition(unsigned short energy, double fat, double saturated,
    double carbonhydrates, double sugars, double fiber, double protein, double salt)
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

bool Ingredient::valid() const
{
    return m_valid;
}
