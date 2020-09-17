import QtQuick 2.4
import Models 1.0

/*
  *@Item home item with UI layout, keyboard event processing, and functions for grid.
  */
Item {
    id: home

    property int gridIndex
    readonly property int gridMaxIndex: 16
    readonly property int windowWidth: appWinWidth
    readonly property int windowHeight: appWinHeight

    // clear grid's number, color and number color.
    function clearGrid() {
        for(gridIndex = 0; gridIndex < gridMaxIndex; gridIndex++) {
            panel.itemNums.itemAt(gridIndex).itemNum = ""
            panel.itemNums.itemAt(gridIndex).color = "white"
            panel.itemNums.itemAt(gridIndex).itemNumColor= "black"
        }
    }

    // show grid's number, color and number color.
    // show score/step.
    // show back button.
    function showGrid() {
        // 1. clear grid
        clearGrid()

        // 2. show grid's data
        for(gridIndex = 0; gridIndex < gridMaxIndex; gridIndex++) {
            if(numController.show(gridIndex)) {
                panel.itemNums.itemAt(gridIndex).itemNum = numController.show(gridIndex)
                panel.itemNums.itemAt(gridIndex).color = numController.color(gridIndex)
                panel.itemNums.itemAt(gridIndex).itemNumColor = numController.numColor(gridIndex)
            }
        }

        // 3. show informatin: score/step.
        infomation.infoScore = numController.score
        infomation.infoBestScore = numController.bestScore
        infomation.infoStep = numController.step
        infomation.infoTotalStep = numController.totalStep

        // 4. show tip: back button
        if(0 < numController.step) {
            tip.tipEnback = true
        }
    }

    // fixed size
    width: windowWidth
    height: windowHeight

    Component.onCompleted: {
        welcomeTimer.start()
    }

    // keyboard event: up down left right
    Keys.onPressed: {
        switch(event.key) {
        case Qt.Key_Up:
            numController.move(Controller.MOVE_UP)
            home.showGrid()
            break
        case Qt.Key_Down:
            numController.move(Controller.MOVE_DOWN)
            home.showGrid()
            break
        case Qt.Key_Left:
            numController.move(Controller.MOVE_LEFT)
            home.showGrid()
            break
        case Qt.Key_Right:
            numController.move(Controller.MOVE_RIGHT)
            home.showGrid()
            break
        default:
            break
        }
    }

    // timer for welcome screen to hide
    Timer {
        id: welcomeTimer
        interval: 1000
        repeat: false
        triggeredOnStart: false
        onTriggered: {
            welcome.visible = false
        }
    }

    // Controller
    Controller { id: numController }
    Connections {
        target: numController
        onGameOver: {
            overTip.visible = true
        }
    }

    // UI layout
    Rectangle {
        anchors.fill: parent
        color: "white"

        // top: information with score/step
        Information { id: infomation }

        // middle: panel with grid
        Item {
            width: home.windowWidth
            height: width
            anchors.top: infomation.bottom
            anchors.horizontalCenter: parent.horizontalCenter

            Panel {
                id: panel
                anchors.centerIn: parent
                onToUp: {
                    numController.move(Controller.MOVE_UP)
                    home.showGrid()
                }
                onToDown: {
                    numController.move(Controller.MOVE_DOWN)
                    home.showGrid()
                }
                onToRight: {
                    numController.move(Controller.MOVE_RIGHT)
                    home.showGrid()
                }
                onToLeft: {
                    numController.move(Controller.MOVE_LEFT)
                    home.showGrid()
                }
            }
        }

        // bottom: tip with start, quit and back button
        Tip {
            id: tip
            anchors.bottom: parent.bottom
            // start button clicked
            onTipStart: {
                numController.start()
                home.showGrid()
                home.focus = true
                tip.tipEnback = false
                panel.enabled = true
                overTip.visible = false
            }
            // quit button clicked
            onQuitTriggered: {
                numController.quitGame()
            }
            // back button clicked
            onTipBack: {
                numController.backTrigger()
                home.showGrid()
                overTip.visible = false
                if(!numController.step) {
                    tip.tipEnback = false
                }
            }
        }

        // fullscreen: welcome screen
        Welcome { id: welcome }
    }

    /* game over tip */
    Over {
        id: overTip
        anchors.centerIn: parent
    }
}
