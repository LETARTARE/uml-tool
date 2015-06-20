/*****************************************************************************
**
** Copyright (C) 2014 Fanaskov Vitaly (vt4a2h@gmail.com)
**
** Created 03/11/2014.
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

#include "application.h"

#include <gui/mainwindow.h>
#include <models/applicationmodel.h>

namespace application {

    /**
     * @brief Application::run
     */
    void Application::run()
    {
        m_MainWindow->show();
    }

    /**
     * @brief Application::Application
     */
    Application::Application(QObject *parent)
        : QObject(parent)
        , m_ApplicationModel(std::make_shared<models::ApplicationModel>())
        , m_MainWindow(std::make_unique<gui::MainWindow>(m_ApplicationModel))
    {
    }

    /**
     * @brief Application::~Application
     */
    Application::~Application()
    {
    }

} // namespace application
