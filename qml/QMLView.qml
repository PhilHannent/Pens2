import QtQuick 2.0

import Pens 1.0 as Pens

Item {

    //Rectangle {
    //    color: "#ff0000"
    //    anchors.fill: parent
    //}

    Repeater {
        id: nodeRepeater
        model: _model

        Pens.PathQuickItem {
            data: model.path
        }
    }
}
