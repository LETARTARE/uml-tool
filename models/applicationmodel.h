/*****************************************************************************
**
** Copyright (C) 2014 Fanaskov Vitaly (vt4a2h@gmail.com)
**
** Created 01/26/2015.
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

#include <QObject>

#include <project/project.h>
#include <db/projectdatabase.h>
#include <entity/scope.h>

#include "projecttreemodel.h"

#include "types.h"

namespace models {

    /// The ApplicationModal class
    class ApplicationModel : public QObject
    {
        Q_OBJECT
    public:
        explicit ApplicationModel(QObject *parent = 0);
        ~ApplicationModel();

        project::SharedProject makeProject();
        project::SharedProject makeProject(const QString &name, const QString &path);
        bool addProject(const project::SharedProject &pr);
        project::SharedProject getProject(const QString &id) const;
        project::ProjectsList projects() const;
        bool removeProject(const QString &id);
        bool containsProject(const QString &id);

        entity::SharedScope makeScope(const QString &name);
        void addExistsScope(const entity::SharedScope &scope);
        void removeScope(const QString &id);

        template <class T = entity::Type>
        std::shared_ptr<T> makeType(const QString &scopeID, const QString &name = "");

        project::SharedProject currentProject() const;
        bool setCurrentProject(const QString &id);

        db::SharedDatabase globalDatabase() const;

        SharedTreeModel treeModel() const;

    private:
        project::Projects m_Projects;
        project::SharedProject m_CurrentProject;

        db::SharedDatabase m_GlobalDatabase;

        SharedTreeModel m_TreeModel;
    };

    template <class T>
    std::shared_ptr<T> ApplicationModel::makeType(const QString &scopeID, const QString &name)
    {
        if (currentProject() && currentProject()->database()) {
            if (auto scope = currentProject()->database()->getScope(scopeID)) {
                if (auto type = scope->addType<T>(name)) {
                    m_TreeModel->addType(type, scope->id(), currentProject()->id());

                    return type;
                }
            }
        }

        return std::shared_ptr<T>(); // stub
    }

} // namespace models
