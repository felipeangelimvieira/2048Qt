import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    id: window
    visible: true
    width: 400
    height: 600
    color: "#faf8ef"
    title: qsTr("2048")

    Rectangle {
        id: table
        x: 141
        y: 228
        width: 350
        height: 350
        color: "#bbada0"
        radius: 6
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 25
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter

        Rectangle {
            id: pos1
            width: 75
            height: 75
            color: "#d4ccc4"
            radius: 3
            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 10
        }

        Rectangle {
            id: pos2
            width: 75
            height: 75
            color: "#d4ccc4"
            radius: 3
            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.left: pos1.right
            anchors.leftMargin: 10
        }

        Rectangle {
            id: pos3
            width: 75
            height: 75
            color: "#d4ccc4"
            radius: 3
            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.leftMargin: 10
            anchors.left: pos2.right
        }

        Rectangle {
            id: pos4
            width: 75
            height: 75
            color: "#d4ccc4"
            radius: 3
            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.leftMargin: 10
            anchors.left: pos3.right
        }

        Rectangle {
            id: pos5
            x: 10
            width: 75
            height: 75
            color: "#d4ccc4"
            radius: 3
            anchors.top: pos1.bottom
            anchors.topMargin: 10
        }

        Rectangle {
            id: pos6
            x: 95
            y: 95
            width: 75
            height: 75
            color: "#d4ccc4"
            radius: 3
        }

        Rectangle {
            id: pos7
            x: 180
            y: 95
            width: 75
            height: 75
            color: "#d4ccc4"
            radius: 3
        }

        Rectangle {
            id: pos8
            x: 265
            y: 95
            width: 75
            height: 75
            color: "#d4ccc4"
            radius: 3
        }

        Rectangle {
            id: pos9
            x: 10
            width: 75
            height: 75
            color: "#d4ccc4"
            radius: 3
            anchors.top: pos5.bottom
            anchors.topMargin: 10
        }

        Rectangle {
            id: pos10
            x: 95
            y: 180
            width: 75
            height: 75
            color: "#d4ccc4"
            radius: 3
        }

        Rectangle {
            id: pos11
            x: 180
            y: 180
            width: 75
            height: 75
            color: "#d4ccc4"
            radius: 3
        }

        Rectangle {
            id: pos12
            x: 265
            y: 180
            width: 75
            height: 75
            color: "#d4ccc4"
            radius: 3
        }

        Rectangle {
            id: pos13
            x: 10
            y: 267
            width: 75
            height: 75
            color: "#d4ccc4"
            radius: 3
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
        }

        Rectangle {
            id: pos14
            x: 95
            y: 265
            width: 75
            height: 75
            color: "#d4ccc4"
            radius: 3
        }

        Rectangle {
            id: pos15
            x: 180
            y: 265
            width: 75
            height: 75
            color: "#d4ccc4"
            radius: 3
        }

        Rectangle {
            id: pos16
            x: 265
            y: 265
            width: 75
            height: 75
            color: "#d4ccc4"
            radius: 3
        }
    }

    Text {
        id: title
        y: 54
        width: 143
        height: 50
        color: "#776e65"
        text: qsTr("2048")
        anchors.verticalCenter: score.verticalCenter
        anchors.bottom: newGame.top
        anchors.bottomMargin: 37
        font.bold: false
        font.family: "Arial"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        anchors.left: table.left
        anchors.leftMargin: 0
        font.pixelSize: 62
    }

    Rectangle {
        id: score
        x: 220
        y: 44
        width: 70
        height: 70
        color: "#bbada0"
        radius: 3
        anchors.bottom: table.top
        anchors.bottomMargin: 111
        anchors.right: table.right
        anchors.rightMargin: 85

        Text {
            id: scoreText
            x: 24
            width: 50
            height: 20
            color: "#faf8ef"
            text: qsTr("SCORE")
            font.bold: true
            font.family: "Arial"
            anchors.top: parent.top
            anchors.topMargin: 5
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: 15
        }
    }

    Rectangle {
        id: best
        x: 305
        y: 44
        width: 70
        height: 70
        color: "#bbada0"
        radius: 3
        anchors.bottom: table.top
        anchors.bottomMargin: 111
        anchors.right: table.right
        anchors.rightMargin: 0

        Text {
            id: bestText
            x: 24
            width: 50
            height: 20
            color: "#faf8ef"
            text: qsTr("BEST")
            font.bold: true
            verticalAlignment: Text.AlignVCenter
            font.family: "Arial"
            font.pixelSize: 15
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 5
            horizontalAlignment: Text.AlignHCenter
        }
    }

    Rectangle {
        id: newGame
        x: 100
        width: 200
        color: "#8f7a66"
        radius: 3
        anchors.top: score.bottom
        anchors.topMargin: 27
        anchors.bottom: table.top
        anchors.bottomMargin: 27
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter

        MouseArea {
            id: mouseArea
            anchors.fill: parent
        }

        Text {
            id: text4
            x: 21
            y: 11
            color: "#f9f6f2"
            text: qsTr("New Game")
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 29
        }
    }
}
