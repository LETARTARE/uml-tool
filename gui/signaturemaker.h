/*****************************************************************************
**
** Copyright (C) 2015 Fanaskov Vitaly (vt4a2h@gmail.com)
**
** Created 03/06/2015.
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

#include <QCoreApplication>
#include <QMap>

#include <models/models_types.hpp>
#include <entity/entity_types.hpp>
#include <project/project_types.hpp>

namespace gui {

    /// The SignatureMaker class
    class SignatureMaker
    {
        Q_DECLARE_TR_FUNCTIONS(SignatureMaker)

    public:
        SignatureMaker();
        SignatureMaker(const models::SharedApplicationModel &model, const project::SharedProject &project,
                       const entity::SharedScope &scope, const entity::SharedType &type);

        ~SignatureMaker();

        QString signature(const entity::SharedBasicEntity &component);

        entity::SharedType type() const;
        void setType(const entity::SharedType &type);

        entity::SharedScope scope() const;
        void setScope(const entity::SharedScope &scope);

        project::SharedProject project() const;
        void setProject(const project::SharedProject &project);

        models::SharedApplicationModel applicationModel() const;
        void setApplicationModel(const models::SharedApplicationModel &applicationModel);

    private:
        QString makeType(const entity::SharedType &type) const;
        QString makeExtType(const entity::SharedExtendedType &type) const;
        QString makeTypeOrExtType(const entity::SharedType &type) const;

        QString typeSignatureById(const QString &id) const;

        QString makeField(const entity::SharedField &field) const;
        QString makeMethod(const entity::SharedMethod &method) const;
        QString makeProperty(const entity::SharedProperty &property) const;

        entity::SharedType findType(const QString &typeId) const;
        entity::SharedScope findScope(const QString &scopeId) const;

        entity::SharedType  m_Type;
        entity::SharedScope m_Scope;
        project::SharedProject m_Project;
        models::SharedApplicationModel m_ApplicationModel;

        using MakerFunction = std::function<QString(const entity::SharedBasicEntity &)>;
        QMap<size_t, MakerFunction> m_MakersMap;
    };

} // namespace gui
