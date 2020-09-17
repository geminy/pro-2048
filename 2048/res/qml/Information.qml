import QtQuick 2.4

/*
  *@Item Information item with score/step.
  */
Rectangle {
    id: info

    property alias infoScore: score.text
    property alias infoBestScore: bestScore.text
    property alias infoStep: step.text
    property alias infoTotalStep: totalStep.text

    // relative size
    width: home.windowWidth
    height: (home.windowHeight - width) * 2 / 3
    color: "lightyellow"

    // 2 x 4
    Grid {
        columns: 4

        Text {
            width: info.width / 4; height: info.height / 2
            text: "Score:"
            color: "blue"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
        Text {
            id: score
            width: info.width / 4; height: info.height / 2
            font.bold: true
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
        }
        Text {
            width: info.width / 4; height: info.height / 2
            text: "Best Score:"
            color: "red"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
        Text {
            id: bestScore
            width: info.width / 4; height: info.height / 2
            font.bold: true
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
        }
        Text {
            width: info.width / 4; height: info.height / 2
            text: "Step:"
            color: "blue"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
        Text {
            id: step
            width: info.width / 4; height: info.height / 2
            font.bold: true
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
        }
        Text {
            width: info.width / 4; height: info.height / 2
            text: "Total Step:"
            color: "red"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
        Text {
            id: totalStep
            width: info.width / 4; height: info.height / 2
            font.bold: true
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
        }
    }
}
