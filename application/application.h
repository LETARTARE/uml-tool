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

#pragma once

#include <QObject>

#include "types.h"

/**
 * @brief namespace application
 */
namespace application {

    /**
     * @brief The Application class
     */
    class Application : public QObject
    {
        Q_OBJECT

    public:
        explicit Application(QObject *parent = nullptr);
        ~Application();

        void run();

        models::SharedApplicationModal m_ApplicationModel;
        gui::UniqueMainWindow m_MainWindow;
    };

} // namespace application
