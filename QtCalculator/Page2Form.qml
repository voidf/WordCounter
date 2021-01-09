import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

Page {
    width: 600
    height: 400
    id: _tree_canvas
    objectName: "sketch"
    property var sonlist: []
    font.pixelSize: Qt.application.font.pixelSize * 1.2
    padding: 10
    property int button_offset_x: 20
    property int button_offset_y: -20
    property int button_size: 100
    property int button_margin: 120
    property var son : Qt.createComponent("TreeNode.qml");
    property var line : Qt.createComponent("Line.qml");
    property int sonctr: 0

    //    property var son_obj: Qt.createComponent("TreeNode.qml")
    function clear_son() {
        console.log(sonlist)
        while(sonlist)sonlist.pop().destroy()
        sonctr=0
    }
    function add_son(px,py,con) {
        var son_obj = son.createObject(_tree_canvas)
        son_obj.x = px
        son_obj.y = py
        son_obj.text = con
        sonlist.push(son_obj)
        sonctr++;
    }
    function add_edge(_x,_y,_X,_Y) {
        var son_obj = line.createObject(_tree_canvas)
        // son_obj.x=_x
        // son_obj.y=_y
        console.log("RECV:",_x,_y,_X,_Y)
        son_obj.lineWidth=4
        son_obj.point1 = Qt.point(_x,_y)
        son_obj.point2 = Qt.point(_X,_Y)

        sonlist.push(son_obj)
        sonctr++;
    }


    Button {
        id: b_clear
        x: _tree_canvas.button_offset_x + 0 * _tree_canvas.button_margin
        y: _tree_canvas.button_offset_y + 1 * _tree_canvas.button_margin

        text: "CLEAR"
        onClicked: {
            clear_son()
        }
    }
    Button {
        id: b_vertex
        x: _tree_canvas.button_offset_x + 0 * _tree_canvas.button_margin
        y: _tree_canvas.button_offset_y + 2 * _tree_canvas.button_margin

        text: "ADD"
        onClicked: {
            add_son(11,45,"14")
        }
    }
    Button {
        id: b_edge
        x: _tree_canvas.button_offset_x + 0 * _tree_canvas.button_margin
        y: _tree_canvas.button_offset_y + 3 * _tree_canvas.button_margin

        text: "EDGE"
        onClicked: {
            add_edge(746,280,608,180)
        }
    }
}
