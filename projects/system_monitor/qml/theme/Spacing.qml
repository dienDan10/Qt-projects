import QtQuick 2.15

QtObject {
	// Base spacing scale in logical pixels.
	readonly property int none: 0
	readonly property int xxxs: 2
	readonly property int xxs: 4
	readonly property int xs: 6
	readonly property int sm: 8
	readonly property int md: 12
	readonly property int lg: 16
	readonly property int xl: 20
	readonly property int xxl: 24
	readonly property int xxxl: 32
	readonly property int huge: 40
	readonly property int giant: 48

	// Common semantic values.
	readonly property int pageMargin: xxl
	readonly property int sectionGap: xl
	readonly property int cardPadding: lg
	readonly property int controlPaddingHorizontal: md
	readonly property int controlPaddingVertical: sm

	// Corner radii.
	readonly property int radiusXs: 4
	readonly property int radiusSm: 6
	readonly property int radiusMd: 8
	readonly property int radiusLg: 12
	readonly property int radiusXl: 16

	// Elevation offsets.
	readonly property int shadowYOffsetSm: 1
	readonly property int shadowYOffsetMd: 2
	readonly property int shadowYOffsetLg: 4
}
