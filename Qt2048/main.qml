import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Extras 1.4
import QtQuick.Controls 2.3

Window {
    id: window

    visible: true
    width: 400
    height: 600
    color: "#faf8ef"
    title: qsTr("2048")

    Rectangle
    {
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        visible: false
    }


    Rectangle {
        id: table
        objectName: "table"
        x: 141
        y: 228
        width: 350
        height: 350
        color: "#bbada0"
        focus: true
        radius: 6
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 25
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter

        Rectangle{
        id: gameOver
        width: parent.width
        height: parent.height
        color: "white"
        opacity: setopacity(game.gameOver)
        visible: true
        z:100
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter

        Behavior on opacity {
            NumberAnimation {
                duration: 1500
                easing.type: Easing.InSine
            }
        }

        Text{
            id: gameOverTxt
            text: "Game over!"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            font.bold: true
            font.family: "Arial"
            color: "#8f7a66"
            font.pixelSize: 36
        }
// cette fonction va gérer la varation de l'opacité de
// la cellule
        function setopacity(bol){
            if (bol === true)
                return 0.7
            return 0
        }
        }

        Keys.onPressed: {
            switch (event.key)
            {
            case Qt.Key_Up:
                game.moveUp();
                break;
            case Qt.Key_Down:
                game.moveDown();
                break
            case Qt.Key_Left:
                game.moveLeft();
                break
            case Qt.Key_Right:
                game.moveRight();
                break
            }
        }

        Cell{
            objectName: "pos1"
            id: pos1
            xpos: cell1.xpos
            ypos: cell1.ypos
            txt: cell1.value
            c: cell1.color
            visible: true
            width: 75
            height: 75
            anchors.top: parent.top
            anchors.topMargin: ypos
            anchors.left: parent.left
            anchors.leftMargin: xpos

        }


        Cell {
            id: pos2
            objectName: "pos2"
            xpos: cell2.xpos
            ypos: cell2.ypos
            txt: cell2.value
            c: cell2.color
            width: 75
            height: 75
            anchors.top: parent.top
            anchors.topMargin: ypos
            anchors.left: parent.left
            anchors.leftMargin: xpos
        }

        Cell {
            id: pos3
            objectName: "pos3"
            xpos: cell3.xpos
            ypos: cell3.ypos
            txt: cell3.value
            c: cell3.color
            width: 75
            height: 75
            anchors.top: parent.top
            anchors.topMargin: ypos
            anchors.left: parent.left
            anchors.leftMargin: xpos
        }

        Cell {
            id: pos4
            objectName: "pos4"
            txt: cell4.value
            c: cell4.color
            xpos: cell4.xpos
            ypos: cell4.ypos
            width: 75
            height: 75
            anchors.top: parent.top
            anchors.topMargin: ypos
            anchors.left: parent.left
            anchors.leftMargin: xpos
        }

        Cell {
            id: pos5
            objectName: "pos5"
            txt: cell5.value
            c: cell5.color
            xpos: cell5.xpos
            ypos: cell5.ypos
            width: 75
            height: 75
            anchors.top: parent.top
            anchors.topMargin: ypos
            anchors.left: parent.left
            anchors.leftMargin: xpos
        }

        Cell {
            id: pos6
            objectName: "pos6"
            txt: cell6.value
            c: cell6.color
            xpos: cell6.xpos
            ypos: cell6.ypos
            width: 75
            height: 75
            anchors.top: parent.top
            anchors.topMargin: ypos
            anchors.left: parent.left
            anchors.leftMargin: xpos
        }

        Cell {
            id: pos7
            objectName: "pos7"
            txt: cell7.value
            c: cell7.color
            xpos: cell7.xpos
            ypos: cell7.ypos
            width: 75
            height: 75
            anchors.top: parent.top
            anchors.topMargin: ypos
            anchors.left: parent.left
            anchors.leftMargin: xpos
        }

        Cell {
            id: pos8
            objectName: "pos8"
            txt: cell8.value
            c: cell8.color
            xpos: cell8.xpos
            ypos: cell8.ypos
            width: 75
            height: 75
            anchors.top: parent.top
            anchors.topMargin: ypos
            anchors.left: parent.left
            anchors.leftMargin: xpos
        }

        Cell {
            id: pos9
            objectName: "pos9"
            txt: cell9.value
            c: cell9.color
            xpos: cell9.xpos
            ypos: cell9.ypos
            width: 75
            height: 75
            anchors.top: parent.top
            anchors.topMargin: ypos
            anchors.left: parent.left
            anchors.leftMargin: xpos
        }

        Cell {
            id: pos10
            objectName: "pos10"
            txt: cell10.value
            c: cell10.color
            xpos: cell10.xpos
            ypos: cell10.ypos
            width: 75
            height: 75
            anchors.top: parent.top
            anchors.topMargin: ypos
            anchors.left: parent.left
            anchors.leftMargin: xpos
        }

        Cell {
            id: pos11
            objectName: "pos11"
            txt: cell11.value
            c: cell11.color
            xpos: cell11.xpos
            ypos: cell11.ypos
            width: 75
            height: 75
            anchors.top: parent.top
            anchors.topMargin: ypos
            anchors.left: parent.left
            anchors.leftMargin: xpos
        }

        Cell {
            id: pos12
            objectName: "pos12"
            txt: cell12.value
            c: cell12.color
            xpos: cell12.xpos
            ypos: cell12.ypos
            width: 75
            height: 75
            anchors.top: parent.top
            anchors.topMargin: ypos
            anchors.left: parent.left
            anchors.leftMargin: xpos
        }

        Cell {
            id: pos13
            objectName: "pos13"
            txt: cell13.value
            c: cell13.color
            xpos: cell13.xpos
            ypos: cell13.ypos
            width: 75
            height: 75
            anchors.top: parent.top
            anchors.topMargin: ypos
            anchors.left: parent.left
            anchors.leftMargin: xpos
        }

        Cell {
            id: pos14
            objectName: "pos14"
            txt: cell14.value
            c: cell14.color
            xpos: cell14.xpos
            ypos: cell14.ypos
            width: 75
            height: 75
            anchors.top: parent.top
            anchors.topMargin: ypos
            anchors.left: parent.left
            anchors.leftMargin: xpos
        }

        Cell {
            id: pos15
            objectName: "pos15"
            txt: cell15.value
            c: cell15.color
            xpos: cell15.xpos
            ypos: cell15.ypos
            width: 75
            height: 75
            anchors.top: parent.top
            anchors.topMargin: ypos
            anchors.left: parent.left
            anchors.leftMargin: xpos
        }

        Cell {
            id: pos16
            objectName: "pos16"
            txt: cell16.value
            c: cell16.color
            xpos: cell16.xpos
            ypos: cell16.ypos
            width: 75
            height: 75
            anchors.top: parent.top
            anchors.topMargin: ypos
            anchors.left: parent.left
            anchors.leftMargin: xpos
        }
// les rectangles suivants vont contruire l'arrière-plan
        Rectangle {
        width: 75
        height: 75
        radius : 3
        color : "#d4ccc4"
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        }

        Rectangle{
        width: 75
        height: 75
        radius : 3
        color : "#d4ccc4"
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 95
        }

        Rectangle{
        width: 75
        height: 75
        radius : 3
        color : "#d4ccc4"
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 180
        }

        Rectangle{
        width: 75
        height: 75
        radius : 3
        color : "#d4ccc4"
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 265
        }

        Rectangle {
        width: 75
        height: 75
        radius : 3
        color : "#d4ccc4"
        anchors.top: parent.top
        anchors.topMargin: 95
        anchors.left: parent.left
        anchors.leftMargin: 10
        }

        Rectangle{
        width: 75
        height: 75
        radius : 3
        color : "#d4ccc4"
        anchors.top: parent.top
        anchors.topMargin: 95
        anchors.left: parent.left
        anchors.leftMargin: 95
        }

        Rectangle{
        width: 75
        height: 75
        radius : 3
        color : "#d4ccc4"
        anchors.top: parent.top
        anchors.topMargin: 95
        anchors.left: parent.left
        anchors.leftMargin: 180
        }

        Rectangle{
        width: 75
        height: 75
        radius : 3
        color : "#d4ccc4"
        anchors.top: parent.top
        anchors.topMargin: 95
        anchors.left: parent.left
        anchors.leftMargin: 265
        }

        Rectangle {
        width: 75
        height: 75
        radius : 3
        color : "#d4ccc4"
        anchors.top: parent.top
        anchors.topMargin: 180
        anchors.left: parent.left
        anchors.leftMargin: 10
        }

        Rectangle{
        width: 75
        height: 75
        radius : 3
        color : "#d4ccc4"
        anchors.top: parent.top
        anchors.topMargin: 180
        anchors.left: parent.left
        anchors.leftMargin: 95
        }

        Rectangle{
        width: 75
        height: 75
        radius : 3
        color : "#d4ccc4"
        anchors.top: parent.top
        anchors.topMargin: 180
        anchors.left: parent.left
        anchors.leftMargin: 180
        }

        Rectangle{
        width: 75
        height: 75
        radius : 3
        color : "#d4ccc4"
        anchors.top: parent.top
        anchors.topMargin: 180
        anchors.left: parent.left
        anchors.leftMargin: 265
        }

        Rectangle {
        width: 75
        height: 75
        radius : 3
        color : "#d4ccc4"
        anchors.top: parent.top
        anchors.topMargin: 265
        anchors.left: parent.left
        anchors.leftMargin: 10
        }

        Rectangle{
        width: 75
        height: 75
        radius : 3
        color : "#d4ccc4"
        anchors.top: parent.top
        anchors.topMargin: 265
        anchors.left: parent.left
        anchors.leftMargin: 95
        }

        Rectangle{
        width: 75
        height: 75
        radius : 3
        color : "#d4ccc4"
        anchors.top: parent.top
        anchors.topMargin: 265
        anchors.left: parent.left
        anchors.leftMargin: 180
        }

        Rectangle{
        width: 75
        height: 75
        radius : 3
        color : "#d4ccc4"
        anchors.top: parent.top
        anchors.topMargin: 265
        anchors.left: parent.left
        anchors.leftMargin: 265
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
        y: 44
        width: 70
        height: 70
        color: "#bbada0"
        radius: 3
        anchors.right: best.left
        anchors.rightMargin: 15
        anchors.bottom: best.top
        anchors.bottomMargin: -70


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

        Text {
            id: scoreValue
            x: 12
            y: 36
            width: 50
            height: 20
            color: "#faf8ef"
            text: game.score
            anchors.horizontalCenterOffset: 0
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottomMargin: 42
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.bold: true
            font.family: "Arial"
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

        Text {
            id: bestValue
            x: 12
            y: 36
            width: 50
            height: 20
            color: "#faf8ef"
            text: game.best
            anchors.horizontalCenterOffset: 0
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottomMargin: 42
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.bold: true
            font.family: "Arial"
            font.pixelSize: 15

        }
    }

    Rectangle {
        id: newGame
        x: 100
        width: 200
        color: mouseArea.containsMouse ? "red" : "#8f7a66"
        radius: 3
        anchors.top: score.bottom
        anchors.topMargin: 27
        anchors.bottom: table.top
        anchors.bottomMargin: 27
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter
        scale:  mouseArea.containsMouse ? 1.1 : 1
        smooth: mouseArea.containsMouse
        MouseArea {
            id: mouseArea
            anchors.fill: parent
            hoverEnabled: true
            onClicked: game.newGame()
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

    Image {
        id: arrowleft
        y: 148
        width: 64
        height: 44
        anchors.verticalCenter: newGame.verticalCenter
        anchors.bottom: table.top
        anchors.bottomMargin: 33
        anchors.left: table.left
        anchors.leftMargin: -16
        opacity: arrowLeftArea.containsMouse ? 0.7 : 0.3
        source: "arrowRight.png"

        MouseArea {
            id: arrowLeftArea
            anchors.fill: parent
            hoverEnabled: true
            onClicked: game.returnArrow()
        }

    }

    Image {
        id: arrowright
        x: 317
        y: 148
        width: 64
        height: 44
        anchors.bottom: table.top
        anchors.bottomMargin: 33
        anchors.right: table.right
        anchors.rightMargin: -16
        anchors.verticalCenter: newGame.verticalCenter
        opacity: arrowRightArea.containsMouse ? 0.7 : 0.3
        source: "arrowLeftt.png"

        MouseArea {

            id: arrowRightArea
            anchors.fill: parent
            hoverEnabled: true
            onClicked: game.forwardArrow()
        }
    }

}
