/*****************************************************************************
**
** Copyright (C) 2015 Fanaskov Vitaly (vt4a2h@gmail.com)
**
** Created 10/05/2015.
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

#include <memory>

#include <QHash>
#include <QMap>

namespace Generator {
    class VirtualFileSystemAbstractItem;
    using SharedVirtualSystemBasicItem = std::shared_ptr<VirtualFileSystemAbstractItem>;
    using VirtualFiles = QHash<QString, SharedVirtualSystemBasicItem>;

    class VirtualFile;
    using SharedVirtualFile = std::shared_ptr<VirtualFile>;

    class VirtualDirectory;
    using SharedVirtualDirectory = std::shared_ptr<VirtualDirectory>;

    class AbstractProjectGenerator;
    using SharedGenerator = std::shared_ptr<AbstractProjectGenerator>;

    using ProfileVariables = QMap<QString,  // name
                                  QString>; // value
}
