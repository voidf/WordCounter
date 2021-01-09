import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    width: 1280
    height: 720
    visible: true
    title: qsTr("Calc")
    objectName: "_ROOT"

    SwipeView {
        id: swipeView
        objectName: "swipeView"
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Page1Form {
        }

        Page2Form {
        }
        
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex

        TabButton {
            text: qsTr("Calculator")
        }
        TabButton {
            text: qsTr("Tree-view")
        }
    }
}
