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

#pragma once

#include "type.h"
#include "types.h"

namespace entity {

    class Field;

    /**
     * @brief The Union class
     */
    class Union : public Type
    {
    public:
        Union();
        Union(Union &&src);
        Union(const Union &src);
        Union(const QString &name, const QString &scopeId);

        Union &operator= (Union rhs);
        Union &operator= (Union &&rhs);
        friend bool operator ==(const Union &lhs, const Union &rhs);

        SharedField getField(const QString &name) const;
        SharedField addField(const QString &name, const QString &typeId);
        void removeField(const QString &name);
        bool containsField(const QString &name);

        FieldsList fields() const;

        QJsonObject toJson() const override;
        void fromJson(const QJsonObject &src, QStringList &errorList) override;

        Union *clone() const;

        bool isEqual(const Union &rhs) const;

    private:
        void moveFrom(Union &src);
        void copyFrom(const Union &src);

        FieldsList m_Fields;
    };

} // namespace entity