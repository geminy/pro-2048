import QtQuick 2.4

/*
  *@Item Panel item for the grid.
  */
Rectangle {
    id: gridPanel

    property var itemNums: itemRepeater
    // mouse point
    property int pressX: 0
    property int pressY: 0
    property int releaseX: 0
    property int releaseY: 0

    // for mouse event
    signal toRight()
    signal toLeft()
    signal toUp()
    signal toDown()

    // mouse direction
    function chooseDirection() {
        if (Math.abs(releaseX - pressX) > Math.abs(releaseY - pressY)) {
            if (releaseX > pressX) {
                toRight()
            }
            else if (releaseX < pressX) {
                toLeft()
            }
        }
        else if (Math.abs(releaseX - pressX) < Math.abs(releaseY - pressY)) {
            if (releaseY > pressY) {
                toDown()
            }
            else if (releaseY < pressY) {
                toUp()
            }
        }
    }

    // relative size
    width: home.windowWidth - radius * 2
    height: width
    radius: 20
    color: "lightblue"
    enabled: false

    // 4 x 4
    Grid {
        id: numGrid
        anchors.centerIn: parent
        columns: 4
        spacing: 10

        Repeater {
            id: itemRepeater
            model: 16

            Cell {
                width: (gridPanel.width - numGrid.spacing * 5) / 4
                height: width
            }
        }
    }

    // mouse event
    MouseArea {
        anchors.fill: parent
        onPressed: {
            pressX = mouse.x
            pressY = mouse.y
        }
        onReleased: {
            releaseX = mouse.x
            releaseY = mouse.y
            chooseDirection()
        }
    }
}
