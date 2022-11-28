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
#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <QObject>
#include <QString>
#include <cassert>
#include <memory>
#include <vector>

class Ingredient : public QObject {
    Q_OBJECT
public:
    explicit Ingredient(const QString& _name, QObject* parent = nullptr);
    explicit Ingredient(const char* _name, QObject* parent = nullptr);
    Ingredient& operator=(const Ingredient& other);
    const QString& name() const;
    unsigned short energy() const;
    void setEnergy(unsigned short newEnergy);
    float fat() const;
    void setFat(float newFat);
    float saturated() const;
    void setSaturated(float newSaturated);
    float carbonhydrates() const;
    void setCarbonhydrates(float newCarbonhydrates);
    float sugars() const;
    void setSugars(float newSugars);
    float fiber() const;
    void setFiber(float newFiber);
    float protein() const;
    void setProtein(float newProtein);
    float salt() const;
    void setSalt(float newSalt);
    void setNutrition(unsigned short energy = 0, float fat = 0, float saturated = 0,
        float carbonhydrates = 0, float sugars = 0, float fiber = 0,
        float protein = 0, float salt = 0);
    bool valid() const;

private:
    const QString m_name;
    unsigned short m_energy { 0 };
    float m_fat { 0 };
    float m_saturated { 0 };
    float m_carbonhydrates { 0 };
    float m_sugars { 0 };
    float m_fiber { 0 };
    float m_protein { 0 };
    float m_salt { 0 };
    bool m_valid { true };
    Q_PROPERTY(QString name READ name);
    Q_PROPERTY(unsigned short energy READ energy WRITE setEnergy);
    Q_PROPERTY(float fat READ fat WRITE setFat);
    Q_PROPERTY(float saturated READ saturated WRITE setSaturated);
    Q_PROPERTY(float carbonhydrates READ carbonhydrates WRITE setCarbonhydrates);
    Q_PROPERTY(float sugars READ sugars WRITE setSugars);
    Q_PROPERTY(float fiber READ fiber WRITE setFiber);
    Q_PROPERTY(float protein READ protein WRITE setProtein);
    Q_PROPERTY(float salt READ salt WRITE setSalt);
    //    Q_PROPERTY(bool valid READ valid);
};

#endif // INGREDIENT_H
