// from ArkUI "frameworks/core/components/common/properties/decoration.h"
/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once
#include "Rect.h"
#include <native_drawing/drawing_types.h>
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_DECORATION_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_DECORATION_H

#include <memory>
#include <optional>
#include <regex>
#include <vector>
#include <react/renderer/graphics/Float.h>
#include "properties/Color.h"
#include "properties/Dimension.h"
#include "properties/Offset.h"

namespace rnoh {

constexpr double CENTER_OFFSET = 50.0;
constexpr double FULL_IMG_SIZE = 100.0;
constexpr double BOX_BEGIN_SIZE = 0.0;
constexpr double BOX_END_SIZE = 100.0;
constexpr double PERCENT_TRANSLATE = 100.0;

enum class GradientDirection {
    LEFT = 0,
    TOP,
    RIGHT,
    BOTTOM,
    LEFT_TOP,
    LEFT_BOTTOM,
    RIGHT_TOP,
    RIGHT_BOTTOM,
    NONE,
    START_TO_END,
    END_TO_START,
};

enum class GradientType {
    LINEAR,
    RADIAL,
    SWEEP,
    CONIC,
};

enum class RadialSizeType {
    CLOSEST_SIDE,
    CLOSEST_CORNER,
    FARTHEST_SIDE,
    FARTHEST_CORNER,
    NONE,
};

enum class RadialShapeType {
    CIRCLE,
    ELLIPSE,
    NONE,
};

enum class SpreadMethod {
    PAD,
    REFLECT,
    REPEAT,
};

enum class BlurStyle {
    NO_MATERIAL = 0,
    THIN,
    REGULAR,
    THICK,
    BACKGROUND_THIN,
    BACKGROUND_REGULAR,
    BACKGROUND_THICK,
    BACKGROUND_ULTRA_THICK,
    COMPONENT_ULTRA_THIN,
    COMPONENT_THIN,
    COMPONENT_REGULAR,
    COMPONENT_THICK,
    COMPONENT_ULTRA_THICK,
};

enum class ThemeColorMode {
    SYSTEM = 0,
    LIGHT,
    DARK,
};

enum class AdaptiveColor {
    DEFAULT = 0,
    AVERAGE,
};

struct BlurOption {
    std::vector<float> grayscale;
};


struct LinearGradientInfo {
    double x1 = 0.0;
    double x2 = 0.0;
    double y1 = 0.0;
    double y2 = 0.0;
};

struct RadialGradientInfo {
    double rx = 0.0;
    double ry = 0.0;
    double cx = 0.0;
    double cy = 0.0;
    double fx = 0.0;
    double fy = 0.0;
};

// indicates which coordinate system to use
enum class Unit {
    objectBoundingBox = 0, // use current node's boundary box
    userSpaceOnUse = 1,    // use rootViewBox
};

inline Unit ToUnit(int value) {
    auto unit = static_cast<Unit>(value);
    if (unit < Unit::objectBoundingBox || unit > Unit::userSpaceOnUse) {
        unit = Unit::objectBoundingBox;
    }
    return unit;
}

class GradientColor final {
public:
    GradientColor() = default;
    ~GradientColor() = default;

    explicit GradientColor(const Color &color) { color_ = color; }

    void SetDimension(double value, DimensionUnit unit = DimensionUnit::PERCENT) {
        if (value < 0.0) {
            return;
        }
        if (unit == DimensionUnit::PERCENT && value > BOX_END_SIZE) {
            return;
        }
        dimension_ = Dimension(value, unit);
    }

    void SetDimension(const Dimension &dimension) {
        if (dimension.Value() < 0.0) {
            return;
        }
        if (dimension.Unit() == DimensionUnit::PERCENT && dimension.Value() > BOX_END_SIZE) {
            return;
        }
        dimension_ = dimension;
    }

    void SetHasValue(bool hasValue) { hasValue_ = hasValue; }

    void SetColor(const Color &color) { color_ = color; }

    const Color &GetColor() const { return color_; }

    const Dimension &GetDimension() const { return dimension_; }

    bool GetHasValue() const { return hasValue_; }

    void SetOpacity(double opacity) { opacity_ = opacity; }

    double GetOpacity() const { return opacity_; }

private:
    bool hasValue_ = true;
    Color color_{Color::TRANSPARENT};
    Dimension dimension_{BOX_END_SIZE, DimensionUnit::PERCENT};
    double opacity_ = 1.0;
};

struct SweepGradient {
    // center of x-axis
    std::optional<Dimension> centerX;
    // center of y-axis
    std::optional<Dimension> centerY;
    // startAngle in degree
    std::optional<Dimension> startAngle;
    // endAngle in degree
    std::optional<Dimension> endAngle;
    // rotation in degree
    std::optional<Dimension> rotation;
};

struct ConicGradient {
    // center of x-axis
    std::optional<Dimension> centerX;
    // center of y-axis
    std::optional<Dimension> centerY;
    // startAngle in radian
    std::optional<Dimension> startAngle;
};

struct RadialGradient {
    // size type
    std::optional<RadialSizeType> radialSizeType;
    // shape circle or ellipse
    std::optional<RadialShapeType> radialShape;
    // size in x-axis
    std::optional<Dimension> radialHorizontalSize;
    // size in y-axis
    std::optional<Dimension> radialVerticalSize;
    // center of shape
    std::optional<Dimension> radialCenterX;
    std::optional<Dimension> radialCenterY;

    std::optional<Dimension> fRadialCenterX;
    std::optional<Dimension> fRadialCenterY;
};

struct LinearGradient {
    // direction in x-axis
    std::optional<GradientDirection> linearX;
    // direction in y-axis
    std::optional<GradientDirection> linearY;
    // angle of gradient line in bearing angle
    std::optional<Dimension> angle;

    std::optional<Dimension> x1;
    std::optional<Dimension> y1;
    std::optional<Dimension> x2;
    std::optional<Dimension> y2;

    // is direction in x-axis
    static bool IsXAxis(GradientDirection direction) {
        return (direction == GradientDirection::LEFT || direction == GradientDirection::RIGHT ||
                direction == GradientDirection::START_TO_END || direction == GradientDirection::END_TO_START);
    }
};

class Gradient final {
public:
    void AddColor(const GradientColor &color);

    void ClearColors();

    bool IsSweepGradientValid() const {
        if (sweepGradient_.startAngle.has_value() && sweepGradient_.endAngle.has_value()) {
            return LessOrEqual(sweepGradient_.startAngle.value().Value(), sweepGradient_.endAngle.value().Value());
        }
        if (sweepGradient_.startAngle.has_value() && !sweepGradient_.endAngle.has_value()) {
            return LessOrEqual(sweepGradient_.startAngle.value().Value(), 0.0);
        }
        if (!sweepGradient_.startAngle.has_value() && sweepGradient_.endAngle.has_value()) {
            return LessOrEqual(0.0, sweepGradient_.endAngle.value().Value());
        }
        return true;
    }

    bool IsValid() const {
        if (GetType() == GradientType::SWEEP) {
            return IsSweepGradientValid() && colors_.size() > 1;
        }
        return colors_.size() > 1;
    }

    void SetRepeat(bool repeat) { repeat_ = repeat; }

    bool GetRepeat() const { return repeat_; }

    const std::vector<GradientColor> &GetColors() const { return colors_; }

    const Offset &GetBeginOffset() const { return beginOffset_; }

    void SetBeginOffset(const Offset &beginOffset) { beginOffset_ = beginOffset; }

    const Offset &GetEndOffset() const { return endOffset_; }

    void SetEndOffset(const Offset &endOffset) { endOffset_ = endOffset; }

    double GetInnerRadius() const { return innerRadius_; }

    void SetInnerRadius(double innerRadius) { innerRadius_ = innerRadius; }

    double GetOuterRadius() const { return outerRadius_; }

    void SetOuterRadius(double outerRadius) { outerRadius_ = outerRadius; }

    GradientType GetType() const { return type_; }

    void SetType(GradientType type) { type_ = type; }

    std::string ToString() const {
        return std::string("Gradient (")
            .append(beginOffset_.ToString())
            .append(",")
            .append(std::to_string(innerRadius_))
            .append(" --- ")
            .append(endOffset_.ToString())
            .append(",")
            .append(std::to_string(outerRadius_))
            .append(")");
    }

    SweepGradient &GetSweepGradient() { return sweepGradient_; }

    const SweepGradient &GetSweepGradient() const { return sweepGradient_; }

    void SetSweepGradient(const SweepGradient &sweepGradient) { sweepGradient_ = sweepGradient; }

    ConicGradient &GetConicGradient() { return conicGradient_; }

    const ConicGradient &GetConicGradient() const { return conicGradient_; }

    void SetConicGradient(const ConicGradient &conicGradient) { conicGradient_ = conicGradient; }

    RadialGradient &GetRadialGradient() { return radialGradient_; }

    const RadialGradient &GetRadialGradient() const { return radialGradient_; }

    void SetRadialGradient(const RadialGradient &radialGradient) { radialGradient_ = radialGradient; }

    LinearGradient &GetLinearGradient() { return linearGradient_; }

    const LinearGradient &GetLinearGradient() const { return linearGradient_; }

    void SetLinearGradient(const LinearGradient &linearGradient) { linearGradient_ = linearGradient; }

    void SetDirection(const GradientDirection &direction) {
        if (LinearGradient::IsXAxis(direction)) {
            linearGradient_.linearX = direction;
        } else {
            linearGradient_.linearY = direction;
        }
    }

    void SetSpreadMethod(SpreadMethod spreadMethod) { spreadMethod_ = spreadMethod; }

    void SetGradientTransform(const std::vector<facebook::react::Float> &gradientTransform) {
        gradientTransform_ = gradientTransform;
    }

    SpreadMethod GetSpreadMethod() const { return spreadMethod_; }

    const std::vector<facebook::react::Float> &GetGradientTransform() const { return gradientTransform_; }

    const RadialGradientInfo &GetRadialGradientInfo() const { return radialGradientInfo_; }

    void SetRadialGradientInfo(const RadialGradientInfo &radialGradientInfo) {
        radialGradientInfo_ = radialGradientInfo;
    }

    const LinearGradientInfo &GetLinearGradientInfo() const { return linearGradientInfo_; }

    void SetLinearGradientInfo(const LinearGradientInfo &linearGradientInfo) {
        linearGradientInfo_ = linearGradientInfo;
    }

    Unit GetGradientUnits() const { return gradientUnits_; }

    void SetGradientUnits(Unit gradientUnits) { gradientUnits_ = gradientUnits; }

private:
    GradientType type_ = GradientType::LINEAR;
    bool repeat_ = false;
    std::vector<GradientColor> colors_;
    // for RadialGradient
    RadialGradient radialGradient_;
    // for LinearGradient
    LinearGradient linearGradient_;
    // for SweepGradient
    SweepGradient sweepGradient_;
    // for ConicGradient
    ConicGradient conicGradient_;
    // used for CanvasLinearGradient
    Offset beginOffset_;
    Offset endOffset_;
    // used for CanvasRadialGradient
    double innerRadius_ = 0.0;
    double outerRadius_ = 0.0;
    SpreadMethod spreadMethod_ = SpreadMethod::PAD;
    Unit gradientUnits_ = Unit::objectBoundingBox;
    std::vector<facebook::react::Float> gradientTransform_;
    LinearGradientInfo linearGradientInfo_;
    RadialGradientInfo radialGradientInfo_;
};


class Pattern final {
public:
    void setPatternX(Dimension x) { x_ = x; }

    void setPatternY(Dimension y) { y_ = y; }

    void setHeight(Dimension height) { height_ = height; }

    void setWidth(Dimension width) { width_ = width; }

    void setPatternUnits(int patternUnits) { patternUnits_ = patternUnits; }

    void setPatternContentUnits(int patternContentUnits) { patternContentUnits_ = patternContentUnits; }

    void setTransform(int patternTransform) { patternTransform_ = patternTransform; }

    void setViewBox(Rect viewBox) { viewBox_ = viewBox; }

    void setImage(OH_Drawing_Image* image) { image_ = image; }

    OH_Drawing_Image* getImage() { return image_ ; }

private:
    Dimension x_; // x-axis default value
    Dimension y_; // y-axis default value
    Dimension width_; // pattern area width default value
    Dimension height_; // pattern area height default value
    int patternUnits_;
    int patternContentUnits_;
    std::string patternTransform_;
    Rect viewBox_;
    OH_Drawing_Image* image_;
};

} // namespace rnoh
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_DECORATION_H
