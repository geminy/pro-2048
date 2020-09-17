import QtQuick 2.4

Rectangle {
    width: 200; height: 150
    radius: 10
    color: "blue"
    opacity: 0.9
    visible: false

    Text {
        text: qsTr("Game Over")
        anchors.centerIn: parent
        color: "red"
        font.pixelSize: 30
        font.bold: true
    }
}
