/*****************************************************************************
**
** Copyright (C) 2015 Fanaskov Vitaly (vt4a2h@gmail.com)
**
** Created 28/12/2015.
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
#include "View.h"

#include <QDropEvent>
#include <QByteArray>
#include <QMimeData>
#include <QDebug>

#include <project/Project.h>
#include <db/ProjectDatabase.h>
#include <commands/CreateEntity.h>
#include <models/ApplicationModel.h>

#include "Elements.h"
#include "QtHelpers.h"

namespace gui {

    /**
     * @brief View::View
     * @param parent
     */
    View::View(const models::SharedApplicationModel &model, QWidget *parent)
        : QGraphicsView(parent)
        , m_ApplicationModel(model)
    {
        setAcceptDrops(true);

        G_CONNECT(appModel().get(), &models::ApplicationModel::currentProjectChanged,
                  this, &View::onCurrentProjectChanged);
    }

    /**
     * @brief View::dropEvent
     * @param de
     */
    void View::dropEvent(QDropEvent *de)
    {
        if (de->mimeData()->hasFormat(Elements::mimeDataType())) {
            QByteArray itemData = de->mimeData()->data(Elements::mimeDataType());
            QDataStream in(&itemData, QIODevice::ReadOnly);

            uint tmpType = uint(entity::KindOfType::Type);
            in >> tmpType;
            Q_ASSERT(in.status() == QDataStream::Ok && tmpType != uint(entity::KindOfType::Type));
            addElement(entity::KindOfType(tmpType), de->pos());

            de->acceptProposedAction();
        }
    }

    /**
     * @brief View::dragEnterEvent
     * @param de
     */
    void View::dragEnterEvent(QDragEnterEvent *de)
    {
        if (de->mimeData()->hasFormat(Elements::mimeDataType()))
            de->acceptProposedAction();
        else
            de->ignore();
    }

    /**
     * @brief View::dragMoveEvent
     * @param de
     */
    void View::dragMoveEvent(QDragMoveEvent *de)
    {
        if (de->mimeData()->hasFormat(Elements::mimeDataType()))
            de->acceptProposedAction();
        else
            de->ignore();
    }

    /**
     * @brief View::dragLeaveEvent
     * @param de
     */
    void View::dragLeaveEvent(QDragLeaveEvent *de)
    {
        de->ignore();
    }

    /**
     * @brief View::onCurrentProjectChanged
     * @param p
     */
    void View::onCurrentProjectChanged(const Projects::SharedProject &,
                                       const Projects::SharedProject &current)
    {
        m_Project = current;
    }

    /**
     * @brief View::project
     * @return
     */
    Projects::SharedProject View::project() const
    {
        return m_Project.lock();
    }

    /**
     * @brief View::appModel
     * @return
     */
    models::SharedApplicationModel View::appModel() const
    {
       return m_ApplicationModel.lock();
    }

    /**
     * @brief View::addElement
     * @param type
     * @param eventPos
     */
    void View::addElement(entity::KindOfType kindOfType, const QPoint &eventPos)
    {
        if (auto pr = project()) {
            auto projectDb = G_ASSERT(pr->database());
            auto scope = G_ASSERT(projectDb->scope(common::ID::projectScopeID()));

            if (auto stack = pr->commandsStack()) {
                auto pos = mapToScene(eventPos);
                if (auto cmd = std::make_unique<Commands::CreateEntity>(kindOfType, scope->id(), pos))
                    stack->push(cmd.release());
            }
        } else {
            qWarning() << Q_FUNC_INFO << ": there is no project.";
        }
    }

} // namespace gui

