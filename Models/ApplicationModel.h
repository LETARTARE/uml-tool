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

#include <Project/Project.h>
#include <DB/ProjectDatabase.h>
#include <Entity/Scope.h>

#include "ProjectTreeModel.h"

#include "types.h"

namespace Models {

    // TODO: handle projects ID changing

    /// The ApplicationModal class
    class ApplicationModel : public QObject
    {
        Q_OBJECT

    public:
        explicit ApplicationModel();
        ~ApplicationModel();

        // TODO: move to some database class
        Projects::SharedProject makeProject();
        Projects::SharedProject makeProject(const QString &name, const QString &path);
        bool addProject(const Projects::SharedProject &pr);
        Projects::SharedProject project(const QString &name) const;
        Projects::ProjectsList projects() const;
        bool removeProject(const QString &name);
        bool containsProject(const QString& name);
        // }

        // TODO: remove from this class (breaks SRP) {
        Entity::SharedScope makeScope(const QString &name);
        void addExistsScope(const Entity::SharedScope &scope);
        void removeScope(const Common::ID &id);

        void addExistsType(const QString &projectName, const Common::ID &scopeID, const Entity::SharedType &type);
        void removeType(const QString &projectName, const Common::ID &scopeID, const Common::ID &typeID);
        // }

        Projects::SharedProject currentProject() const;
        bool setCurrentProject(const QString &name);

        DB::SharedDatabase globalDatabase() const;
        void setGlobalDatabse(const DB::SharedDatabase &db);

        SharedTreeModel treeModel() const;

    signals:
        void scopeAdded(const Entity::SharedScope &scope);
        void currentProjectChanged(const Projects::SharedProject &previous,
                                   const Projects::SharedProject &current);

    private:
        Projects::Projects m_Projects;
        Projects::SharedProject m_CurrentProject;

        DB::SharedDatabase m_GlobalDatabase;

        SharedTreeModel m_TreeModel;
    };

} // namespace models
