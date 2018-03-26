import QtQuick 2.0
import QtQuick.Controls 2.3

Item {
    property string txt
    property color c: "#d4ccc4"
Rectangle {
    width: 75; height: 75
    color: c
    visible: true
    radius : 3
    z:10
    Text{
        anchors.centerIn: parent
        text: txt
        font.family: "Helvetica"
        font.pointSize: 20
        color: "white"
    }
}

}
