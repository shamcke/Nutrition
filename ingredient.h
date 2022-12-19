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
    double fat() const;
    void setFat(double newFat);
    double saturated() const;
    void setSaturated(double newSaturated);
    double carbonhydrates() const;
    void setCarbonhydrates(double newCarbonhydrates);
    double sugars() const;
    void setSugars(double newSugars);
    double fiber() const;
    void setFiber(double newFiber);
    double protein() const;
    void setProtein(double newProtein);
    double salt() const;
    void setSalt(double newSalt);
    void setNutrition(unsigned short energy = 0, double fat = 0, double saturated = 0,
        double carbonhydrates = 0, double sugars = 0, double fiber = 0,
        double protein = 0, double salt = 0);
    bool valid() const;

private:
    const QString m_name;
    unsigned short m_energy { 0 };
    double m_fat { 0 };
    double m_saturated { 0 };
    double m_carbonhydrates { 0 };
    double m_sugars { 0 };
    double m_fiber { 0 };
    double m_protein { 0 };
    double m_salt { 0 };
    bool m_valid { true };
    Q_PROPERTY(QString name READ name);
    Q_PROPERTY(unsigned short energy READ energy WRITE setEnergy);
    Q_PROPERTY(double fat READ fat WRITE setFat);
    Q_PROPERTY(double saturated READ saturated WRITE setSaturated);
    Q_PROPERTY(double carbonhydrates READ carbonhydrates WRITE setCarbonhydrates);
    Q_PROPERTY(double sugars READ sugars WRITE setSugars);
    Q_PROPERTY(double fiber READ fiber WRITE setFiber);
    Q_PROPERTY(double protein READ protein WRITE setProtein);
    Q_PROPERTY(double salt READ salt WRITE setSalt);
    //    Q_PROPERTY(bool valid READ valid);
};

#endif // INGREDIENT_H
