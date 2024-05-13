// from ArkUI "frameworks/core/components_ng/svg/parse/svg_attributes_parser.h"

#pragma once
#include <string>
// #include "base/memory/ace_type.h"
// #include "base/utils/noncopyable.h"
#include "properties/Color.h"
#include "properties/PaintState.h"
#include "properties/Dimension.h"
#include "properties/Rect.h"
#include "properties/Decoration.h"

namespace rnoh {
class SvgAttributesParser {
public:
    static Color GetColor(const std::string& str);
    static LineCapStyle GetLineCapStyle(const std::string& val);
    static LineJoinStyle GetLineJoinStyle(const std::string& val);
    static Dimension ParseDimension(const std::string& value, bool useVp = false);
    static double ParseDouble(const std::string& value);
};

enum class SvgFeColorMatrixType {
    MATRIX,
    SATURATE,
    HUE_ROTATE,
    LUMINACE_TO_ALPHA,
};

enum class SvgColorInterpolationType {
    LINEAR_RGB,
    SRGB,
    AUTO
};

enum class SvgFeInType {
    SOURCE_GRAPHIC,
    SOURCE_ALPHA,
    BACKGROUND_IMAGE,
    BACKGROUND_ALPHA,
    FILL_PAINT,
    STROKE_PAINT,
    PRIMITIVE
};

enum class SvgFeEdgeMode {
    EDGE_DUPLICATE,
    EDGE_WRAP,
    EDGE_NONE
};

enum class SvgFeOperatorType {
    FE_ARITHMETIC,
    FE_ATOP,
    FE_IN,
    FE_LIGHTER,
    FE_OUT,
    FE_OVER,
    FE_XOR
};

enum class SvgFeBlendMode {
    NORMAL,
    MULTIPLY,
    SCREEN,
    DARKEN,
    LIGHTEN
};

struct SvgFeIn {
    SvgFeInType in = SvgFeInType::PRIMITIVE;
    std::string id;
};

struct SvgAttributes {
    Dimension vbX;
    Dimension vbY;
    Dimension vbWidth;
    Dimension vbHeight;
    Dimension x;
    Dimension y;
    Dimension width = -1.0_px;
    Dimension height = -1.0_px;
    bool autoMirror = false;
    std::string align;
    int meetOrSlice;
};

struct SvgAnimateAttribute {
    std::string attributeName;
    int32_t begin = 0;
    int32_t dur = 0;
    int32_t end = 0;
    int32_t repeatCount = 1;
    std::string fillMode;
    std::string calcMode;
    std::vector<std::string> values;
    std::vector<double> keyTimes;
    std::vector<std::string> keySplines;
    std::string from;
    std::string to;
    std::vector<std::string> keyPoints;
    std::string path;
    std::string rotate;
    std::string transformType;
};

// struct SvgStopAttribute {
//     GradientColor gradientColor;
// };

struct SvgRectAttribute {
    Dimension x;
    Dimension y;
    Dimension rx = -1.0_px;
    Dimension ry = -1.0_px;
    Dimension width;
    Dimension height;
};

struct SvgMaskAttribute {
    Dimension x = Dimension(-0.1, DimensionUnit::PERCENT); // x-axis default value
    Dimension y = Dimension(-0.1, DimensionUnit::PERCENT); // y-axis default value
    Dimension width = Dimension(1.2, DimensionUnit::PERCENT); // masking area width default value
    Dimension height = Dimension(1.2, DimensionUnit::PERCENT); // masking area height default value
    std::string maskContentUnits = "userSpaceOnUse";
    std::string maskUnits = "objectBoundingBox";
};

struct SvgCircleAttribute {
    Dimension cx;
    Dimension cy;
    Dimension r;
};

struct SvgPolygonAttribute {
    std::string points;
};

struct SvgEllipseAttribute {
    Dimension cx;
    Dimension cy;
    Dimension rx = -1.0_px;
    Dimension ry = -1.0_px;
};

struct SvgLineAttribute {
    Dimension x1;
    Dimension y1;
    Dimension x2;
    Dimension y2;
};

// struct SvgPatternAttribute {
//     Dimension x; // x-axis default value
//     Dimension y; // y-axis default value
//     Dimension width; // pattern area width default value
//     Dimension height; // pattern area height default value
//     int patternUnits;
//     int patternContentUnits;
//     std::string patternTransform;
//     Rect viewBox;
// };

struct SvgImageAttribute {
    Dimension x = Dimension(0, DimensionUnit::PX); // x-axis default value
    Dimension y = Dimension(0, DimensionUnit::PX); // y-axis default value
    Dimension width = Dimension(0.0, DimensionUnit::PX); // image width default value
    Dimension height = Dimension(0.0, DimensionUnit::PX); // image height default value
    std::string href = "";
};

struct SvgFilterAttribute {
    Dimension x = Dimension(-0.1, DimensionUnit::PERCENT); // x-axis default value
    Dimension y = Dimension(-0.1, DimensionUnit::PERCENT); // y-axis default value
    Dimension width = Dimension(1.2, DimensionUnit::PERCENT); // masking area width default value
    Dimension height = Dimension(1.2, DimensionUnit::PERCENT); // masking area height default value
};

struct SvgFeCommonAttribute {
    Dimension x = Dimension(0.0, DimensionUnit::PERCENT);
    Dimension y = Dimension(0.0, DimensionUnit::PERCENT);
    Dimension height = Dimension(1.0, DimensionUnit::PERCENT);
    Dimension width = Dimension(1.0, DimensionUnit::PERCENT);
    std::string result;
    SvgFeIn in;
    SvgColorInterpolationType colorInterpolationType = SvgColorInterpolationType::SRGB;
};

struct SvgFeFloodAttribute {
    Color floodColor = Color::BLACK;
    double floodOpacity = 1.0;
};

struct SvgFeGaussianBlurAttribute {
    float stdDeviationX = 0.0f;
    float stdDeviationY = 0.0f;
    SvgFeEdgeMode edgeMode = SvgFeEdgeMode::EDGE_DUPLICATE;
};

struct SvgFeOffsetAttribute {
    Dimension dx;
    Dimension dy;
};

struct SvgFeCompositeAttribute {
    SvgFeIn in2;
    SvgFeOperatorType operatorType = SvgFeOperatorType::FE_OVER;
    float k1 = 0.0f;
    float k2 = 0.0f;
    float k3 = 0.0f;
    float k4 = 0.0f;
};

struct SvgFeBlendAttribute {
    SvgFeIn in2;
    SvgFeBlendMode blendMode = SvgFeBlendMode::NORMAL;
};

struct SvgFeColorMatrixAttribute {
    SvgFeColorMatrixType type = SvgFeColorMatrixType::MATRIX;
    std::string values;
};

struct SvgGradientAttribute {
    Gradient gradient = Gradient();
};

struct SvgPatternAttribute {
    Pattern pattern = Pattern();
};
} // namespace rnoh