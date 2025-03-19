import QtQuick 2.4
import QtQuick.Window 2.2
import CustomControls 1.0

Window {
    visible: true
    width: 1280
    height: 720
    title: "Font Trial"

    Rectangle {
        id: background
        anchors.fill: parent
        color: "black"

        BlackScreenView {
            anchors.fill: parent
            focus: true
        }
    }
}
