import QtQuick 2.4
import QtQuick.Controls 1.3

/*
  *@Item tip item with start, quit and back button.
  */
Item {
    property alias tipEnback: back.enabled

    // triggered by start button
    signal tipStart()
    // triggered by quit button
    signal quitTriggered()
    // triggered by back button
    signal tipBack()


    // relative size
    width: home.windowWidth
    height: (home.windowHeight - width) / 3

    // start button
    Button {
        width: parent.width / 3
        height: parent.height
        text: qsTr("Start")
        onClicked: parent.tipStart()
    }

    // quit button
    Button {
        width: parent.width / 3
        height: parent.height
        x: width
        text: qsTr("Quit")
        onClicked: parent.quitTriggered()
    }

    // back button
    Button {
        id: back
        enabled: false
        width: parent.width / 3
        height: parent.height
        x: width * 2
        text: qsTr("Back")
        onClicked: parent.tipBack()
    }
}
