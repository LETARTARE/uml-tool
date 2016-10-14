/*****************************************************************************
**
** Copyright (C) 2016 Fanaskov Vitaly (vt4a2h@gmail.com)
**
** Created 15/09/2016.
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

#include <QtGui/QGraphicsScene>

#include <entity/EntityFactory.h>

#include <models/ApplicationModel.h>

#include <gui/graphics/GraphicsTypes.h>
#include <gui/graphics/Scene.h>

#include "TestProjectBase.h"

class CommandsTester : public ProjectBase
{
protected:
    CommandsTester()
    {
    }

    void SetUp() override
    {
        m_FakeAppModel = std::make_shared<models::ApplicationModel>();
        m_FakeAppModel->setGlobalDatabse(m_GlobalDb);
        m_FakeAppModel->addProject(m_Project);
        m_FakeAppModel->setCurrentProject(m_Project->name());

        m_Scene = std::make_unique<graphics::Scene>();
        const_cast<entity::EntityFactory &>(
            entity::EntityFactory::instance()).onSceneChanged(m_Scene.get());
    }

    void TearDown() override
    {
        m_FakeAppModel.reset();
        m_Scene.reset();
    }

    models::SharedApplicationModel m_FakeAppModel;
    graphics::UniqueScene m_Scene;
};
