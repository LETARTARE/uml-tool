/*****************************************************************************
**
** Copyright (C) 2014 Fanaskov Vitaly (vt4a2h@gmail.com)
**
** Created 29/10/2014.
**
** This file is part of Q-UML (UML tool for Qt).
**
** Q-UML is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** Q-UML is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.

** You should have received a copy of the GNU Lesser General Public License
** along with Q-UML.  If not, see <http://www.gnu.org/licenses/>.
**
*****************************************************************************/

#include "enum.h"
#include "constants.cpp"
#include "enums.h"

#include <algorithm>
#include <utility>

#include <QJsonObject>
#include <QStringList>
#include <QJsonArray>

#include <utility/helpfunctions.h>

namespace entity {

    /**
     * @brief Variable::toJson
     * @return
     */
    QJsonObject Variable::toJson() const
    {
        QJsonObject result;
        result.insert("Name", first);
        result.insert("Number", second);

        return result;
    }

    /**
     * @brief Variable::fromJson
     * @param src
     * @param errorList
     */
    void Variable::fromJson(const QJsonObject &src, QStringList &errorList)
    {
        utility::checkAndSet(src, "Name",   errorList, [&src, this](){ first  = src["Name"].toString(); });
        utility::checkAndSet(src, "Number", errorList, [&src, this](){ second = src["Number"].toInt();  });
    }

    /**
     * @brief Variable::hashType
     * @return
     */
    size_t Variable::hashType() const
    {
        return Variable::staticHashType();
    }

    /**
     * @brief Variable::staticHashType
     * @return
     */
    size_t Variable::staticHashType()
    {
        return typeid(Variable).hash_code();
    }

    /**
     * @brief Enum::Enum
     */
    Enum::Enum()
        : Enum(DEFAULT_NAME, GLOBAL_SCOPE_ID)
    {
    }

    /**
     * @brief Enum::Enum
     * @param name
     * @param scopeId
     */
    Enum::Enum(const QString &name, const QString &scopeId)
        : Type(name, scopeId)
        , m_EnumTypeId(STUB_ID)
        , m_StrongStatus(false)
    {
    }

    /**
     * @brief operator ==
     * @param lhs
     * @param rhs
     * @return
     */
    bool operator==(const Enum &lhs, const Enum &rhs)
    {
        return static_cast<const Type&>(lhs).isEqual(rhs) &&
               lhs.m_EnumTypeId   == rhs.m_EnumTypeId     &&
               lhs.m_StrongStatus == rhs.m_StrongStatus   &&
               lhs.m_Variables    == rhs.m_Variables;
    }

    /**
     * @brief Enum::isStrong
     * @return
     */
    bool Enum::isStrong() const
    {
        return m_StrongStatus;
    }

    /**
     * @brief Enum::setStrongStatus
     * @param status
     */
    void Enum::setStrongStatus(bool status)
    {
        m_StrongStatus = status;
    }

    /**
     * @brief Enum::addVariable
     * @param name
     * @return
     */
    Variable &Enum::addVariable(const QString &name)
    {
        m_Variables.append(Variable(name, m_Variables.size()));
        return m_Variables.last();
    }

    /**
     * @brief Enum::getVariable
     * @param name
     * @return
     */
    Variable Enum::getVariable(const QString &name) const
    {
        auto it = std::find_if(m_Variables.cbegin(), m_Variables.cend(),
                               [&name](const Variable &v){ return v.first == name; });
        return (it != m_Variables.end() ? *it : Variable(DEFAULT_NAME, -1));
    }

    /**
     * @brief Enum::removeVariable
     * @param name
     */
    void Enum::removeVariable(const QString &name)
    {
        auto it = std::find_if(m_Variables.begin(), m_Variables.end(),
                               [&name](Variable &v){ return v.first == name; });
        if (it != m_Variables.end()) m_Variables.erase(it);
    }

    /**
     * @brief Enum::containsVariable
     * @param name
     * @return
     */
    bool Enum::containsVariable(const QString &name)
    {
        return (std::find_if(m_Variables.begin(), m_Variables.end(),
                            [&name](Variable &v){ return v.first == name; }) !=
                m_Variables.end());
    }

    /**
     * @brief Enum::variables
     * @return
     */
    VariablesList Enum::variables() const
    {
        return m_Variables;
    }

    /**
     * @brief Enum::enumTypeId
     * @return
     */
    QString Enum::enumTypeId() const
    {
        return m_EnumTypeId;
    }

    /**
     * @brief Enum::setEnumTypeId
     * @param enumTypeId
     */
    void Enum::setEnumTypeId(const QString &enumTypeId)
    {
        m_EnumTypeId = enumTypeId;
    }

    /**
     * @brief Enum::toJson
     * @return
     */
    QJsonObject Enum::toJson() const
    {
        QJsonObject result(Type::toJson());

        result.insert("Enum type id", m_EnumTypeId);
        result.insert("Strong status", m_StrongStatus);

        QJsonArray variables;
        for (auto &&v : m_Variables)
            variables.append(v.toJson());

        result.insert("Variables", variables);

        return result;
    }

    /**
     * @brief Enum::fromJson
     * @param src
     * @param errorList
     */
    void Enum::fromJson(const QJsonObject &src, QStringList &errorList)
    {
        Type::fromJson(src, errorList);

        utility::checkAndSet(src, "Enum type id",  errorList, [&src, this](){ m_EnumTypeId   = src["Enum type id"].toString(); });
        utility::checkAndSet(src, "Strong status", errorList, [&src, this](){ m_StrongStatus = src["Strong status"].toBool();  });

        m_Variables.clear();
        utility::checkAndSet(src, "Variables", errorList, [&src, &errorList, this](){
            if (src["Variables"].isArray()) {
                for (auto &&value : src["Variables"].toArray())
                    m_Variables.append(Variable(value.toObject(), errorList));
            } else {
                errorList << "Error: \"Varibles\" is not array";
            }
        });
    }

    /**
     * @brief Enum::hashType
     * @return
     */
    size_t Enum::hashType() const
    {
        return Enum::staticHashType();
    }

    /**
     * @brief Enum::staticHashType
     * @return
     */
    size_t Enum::staticHashType()
    {
        return typeid(Enum).hash_code();
    }

    /**
     * @brief Enum::marker
     * @return
     */
    QString Enum::marker() const
    {
        return Enum::staticMarker();
    }

    /**
     * @brief Enum::staticMarker
     * @return
     */
    QString Enum::staticMarker()
    {
        return "Enum";
    }

    /**
     * @brief Enum::isEqual
     * @param rhs
     * @return
     */
    bool Enum::isEqual(const Enum &rhs) const
    {
        return *this == rhs;
    }

} // namespace entity
