import QtQuick 2.4

/*
  *@Item Cell item for one number.
  */
Rectangle {
    property alias itemNum: innerNum.text
    property alias itemNumColor: innerNum.color

    radius: 10

    Behavior on color {
        PropertyAnimation {
            duration: 100
        }
    }

    Text {
        id: innerNum
        anchors.centerIn: parent
    }
}
