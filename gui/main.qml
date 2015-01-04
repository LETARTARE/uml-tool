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

import QtQuick 2.4
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import QtQuick.Window 2.0
import QtQuick.Dialogs 1.2
import QUMLCore 1.0

import "Helpers.js" as Helpers

ApplicationWindow {
    id: appWindow
    visible: true
    width: 800
    height: 600
    x: Screen.width / 2 - width / 2
    y: Screen.height / 2 - height / 2
    title: qsTr("Q-UML")

    property int projectStatus

    signal projectModified

    menuBar: MenuBar {
        id: menuBar
        Menu {
            id: menuFile
            title: qsTr("&File")
            MenuItem {
                id: itemNewProject
                action: actionNewProject
            }
            MenuItem {
                id: itemOpenProject
                action: actionOpenProject
            }
            MenuItem {
                id: itemSaveProject
                action: actionSaveProject
            }
            MenuSeparator {}
            MenuItem {
                id: itemExit
                action: actionExit
            }

            Action {
                id: actionNewProject
                text: qsTr("Create &new project")
                tooltip: qsTr("Press to create new project")
                shortcut: "Ctrl+N"
                onTriggered: newProjectDialog.show()
            }
            Action {
                id: actionOpenProject
                text: qsTr("&Open project")
                tooltip: qsTr("Press to open existing project")
                shortcut: "Ctrl+O"
                onTriggered: openNewProjectDialog.open()
            }
            Action {
                id: actionSaveProject
                text: qsTr("&Save project")
                tooltip: qsTr("Press to save current project")
                shortcut: "Ctrl+S"
                onTriggered: saveProject()
            }
            Action {
                id: actionExit
                text: qsTr("&Exit")
                tooltip: qsTr("Press to close application")
                shortcut: "Ctrl+Q"
                onTriggered: Qt.quit()
            }

            FileDialog {
                id: openNewProjectDialog
                title: qsTr("Open new project")
                nameFilters: "Q-UML project files (*.qut)"
                onAccepted: {
                    if (Qt.resolvedUrl(fileUrl))
                        application.openProject(fileUrl.toString().replace("file://", ""))
                    else
                      handleErrors(qsTr("Path: %1").arg(fileUrl), qsTr("is not resolved."))
                }
            }
        }
    }

    // simple stub for test class creation mechanism
    toolBar: ToolBar {
        id: tbEntityActions
        RowLayout {
            id: rowLayout
            anchors.fill: parent
            ToolButton {
                id: btnCreateClass
                action: actionCreateClass
            }

            Action {
               id: actionCreateClass
               text: qsTr("Add class")
               tooltip: qsTr("Press to add class")
               shortcut: "Ctrl+Shift+C"
               checkable: true
            }
        }
    }

    MainScene {
        id: mainScene
        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
            bottom: parent.bottom
        }
    }

    MessageDialog {
        id: warningMessage
        modality: Qt.ApplicationModal
        icon: StandardIcon.Warning
        title: qsTr("Found a few problems")
        standardButtons: StandardButton.Ok

        function addErrors(msg, errorList) {
            text = msg
            informativeText = errorList.join("\n")
        }
    }

    NewProjectDialog {
        id: newProjectDialog
    }

    Connections {
        target: application
        onErrors: handleErrors(message, errorlist)
        onProjectCreated: handleOpenProject(project)
        onProjectOpened: handleOpenProject(project)
        onProjectChanged: handleProjectChanged()
    }

    Connections {
        target: appWindow
        onProjectStatusChanged: changeProjectStatus(projectStatus)
    }

    Connections {
        target: mainScene
        onClicked: createNewEntity(x, y)
    }

    Component.onCompleted: {
        projectStatus = QUMLApplication.NoProject
        actionSaveProject.enabled = false;
    }

    function handleProjectChanged() {
        if (oldProject !== null) {
            oldProject.saved.disconnect(appWindow.makeTitle)
            oldProject.modified.disconnect(appWindow.makeTitle)
            oldProject.errors.disconnect(appWindow.handleErrors)
            appWindow.projectModified.disconnect(oldProject.touch)
        }

        if (currentProject !== null) {
            // TODO: check it maybe not disconnected!
            currentProject.saved.connect(function() {
                appWindow.makeTitle(currentProject.name, false)
                actionSaveProject.enabled = false
            })
            currentProject.modified.connect(function() {
                appWindow.makeTitle(currentProject.name, true)
                actionSaveProject.enabled = true
            })
            currentProject.errors.connect(appWindow.handleErrors)
            appWindow.projectModified.connect(currentProject.touch)
        }

        actionSaveProject.enabled = false
        mainScene.clear()
        // TODO: clear scene!
    }

    function changeProjectStatus(newStatus) {
        // NOTE: add dictionary with callbacks for more statuses
        switch (newStatus) {
            case QUMLApplication.ProjectOpened:
                setOpenProjectStatus();
                break;
            case QUMLApplication.NoProject:
                setNoProjectStatus();
                break;
            default:
                console.log("Strange project status: %1!".arg(newStatus))
        }
    }

    function setOpenProjectStatus() {
        mainScene.activeStatus = true
        tbEntityActions.enabled = true
    }

    function setNoProjectStatus() {
        mainScene.activeStatus = false
        tbEntityActions.enabled = false
    }

    function handleErrors(msg, errors) {
        warningMessage.addErrors(msg, errors)
        warningMessage.open()
    }

    function handleOpenProject(project) {
        makeTitle(project.Name, false)
        projectStatus = QUMLApplication.ProjectOpened
    }

    function saveProject() {
        if (currentProject !== null)
            currentProject.save()
        else
            handleErrors(qsTr("Save error."), ["No current project."])
    }

    function handleSuccess(msg, details) {
        stub.text = msg + " " + details
    }

    function makeTitle(projectName, withAsterisks) {
        var title = "%1%2 - Q-UML"
        appWindow.title = title.arg(projectName).arg(withAsterisks ? " *" : "")
    }

    function createNewEntity(x, y) {
        if (actionCreateClass.checked) {
            var component = Qt.createComponent("EntityItem.qml")
            if (component.status === Component.Ready) {
                var entity = component.createObject(mainScene)
                if (entity !== null) {
                    entity.x = (x - entity.width / 2).clamp(0, mainScene.width - entity.width)
                    entity.y = (y - entity.height / 2).clamp(0, mainScene.height - entity.height)
                    entity.objectName = "entity"

                    // TODO: add enumeration parameter for type
                    var jsObj = currentProjectDatabase.createEntity(application.currentScopeID);
                    entity.dataFromJson(jsObj)
                }
            } else if (component.status === Component.Error) {
                handleErrors(qsTr("Component creation error"), qsTr("Creation QML component faild."))
            }

            actionCreateClass.checked = false
        }
    }
}
