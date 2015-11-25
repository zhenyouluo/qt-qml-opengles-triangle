import QtQuick 2.5
import QOETDemo 1.0

Item {
	width: 480
	height: 320

	GLESTriangleView {
		anchors.fill: parent
		focus: true
	}

	Rectangle {
		id: label
		height: 20

		anchors.right: parent.right
		anchors.bottom: parent.bottom
		anchors.left: parent.left

		Text {
			anchors.centerIn: parent
			color: "#000000"
			text: "Keep left mouse button pressed while moving to rotate"
		}
	}
}
