import QtQuick 2.4
import QtQuick.Window 2.2
import QtQuick.Controls 1.3
import CustomControls 1.0

ApplicationWindow {
    id: root
    title: qsTr("Font Trial")
    width: 1280
    height: 720
    visible: true

    Rectangle {
        anchors.fill: parent
        color: "black"
        focus: !contentLoader.sourceComponent

        Keys.onSelectPressed: {
            if (!contentLoader.sourceComponent) {
                contentLoader.sourceComponent = contentViewComponent
                contentLoader.forceActiveFocus();
            }
        }
        
        Keys.onEnterPressed: {
            if (!contentLoader.sourceComponent) {
                contentLoader.sourceComponent = contentViewComponent
                contentLoader.forceActiveFocus();
            }
        }

        Button {
            id: selectButton
            anchors.centerIn: parent
            text: "Select"
            visible: !contentLoader.sourceComponent
            onClicked: contentLoader.sourceComponent = contentViewComponent
        }

        Loader {
            id: contentLoader
            anchors.fill: parent
        }
    }

    Component {
        id: contentViewComponent
        ContentView {
            width: root.width
            height: root.height
            onBackPressed: {
                contentLoader.sourceComponent = null
                selectButton.visible = true
            }
            Component.onCompleted: {
                initialize()
            }
        }
    }
}
