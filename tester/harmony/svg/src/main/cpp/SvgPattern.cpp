/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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


#include "SvgPattern.h"
#include <native_drawing/drawing_matrix.h>
#include <native_drawing/drawing_image.h>
#include <native_drawing/drawing_brush.h>
#include <native_drawing/drawing_canvas.h>
#include <native_drawing/drawing_bitmap.h>
#include <native_drawing/drawing_shader_effect.h>
#include <native_drawing/drawing_sampling_options.h>
#include <native_drawing/drawing_color.h>

namespace rnoh {

SvgPattern::SvgPattern() { LOG(INFO) << "[SvgPattern] init"; }

void SvgPattern::OnDrawTraversedBefore(OH_Drawing_Canvas *canvas) {
    LOG(INFO) << "[pattern] OnDrawTraversedBefore";
    // 1.
}

void SvgPattern::OnDrawTraversedAfter(OH_Drawing_Canvas *canvas) {
    LOG(INFO) << "[pattern] OnDrawTraversedAfter";
    //     OH_Drawing_CanvasRestore(canvas);
}

// void SvgPattern::ConcatMatrix(OH_Drawing_Canvas *canvas) {
//     Rect vbRect = patternAttr_.viewBox;
//     Rect eRect = Rect(patternAttr_.x.ConvertToPx(), patternAttr_.y.ConvertToPx(), patternAttr_.width.ConvertToPx(),
//                       patternAttr_.height.ConvertToPx());
//     double vbX = vbRect.Left();
//     double vbY = vbRect.Top();
//     double vbWidth = vbRect.Width();
//     double vbHeight = vbRect.Height();
//
//     // Let e-x, e-y, e-width, e-height be the position and size of the element respectively.
//     double eX = eRect.Left();
//     double eY = eRect.Top();
//     double eWidth = eRect.Width();
//     double eHeight = eRect.Height();
//
//     // Initialize scale-x to e-width/vb-width.
//     double scaleX = eWidth / vbWidth;
//
//     // Initialize scale-y to e-height/vb-height.
//     double scaleY = eHeight / vbHeight;
//
//     // Initialize translate-x to e-x - (vb-x * scale-x).
//     // Initialize translate-y to e-y - (vb-y * scale-y).
//     double translateX = eX - (vbX * scaleX);
//     double translateY = eY - (vbY * scaleY);
//
//     OH_Drawing_Matrix *matrix = OH_Drawing_MatrixCreate();
//     OH_Drawing_MatrixSetMatrix(matrix, scaleX, 0, translateX, scaleY, translateY, 0, 0, 0, 1.0);
//     OH_Drawing_CanvasConcatMatrix(canvas, matrix);
//     OH_Drawing_MatrixDestroy(matrix);
// }
//
// void SvgPattern::SaveDefinition(OH_Drawing_Canvas *canvas) {
//     LOG(INFO) << "SaveDefinition";
//     OH_Drawing_Canvas *newCanvas = OH_Drawing_CanvasCreate();
//     ConcatMatrix(newCanvas);
//
//     auto scale_ = 3.25010318;
//     if (patternAttr_.patternUnits) {
//         LOG(INFO) << "SaveDefinition patternUnits";
//         OH_Drawing_CanvasScale(newCanvas, patternAttr_.width.ConvertToPx() / scale_,
//                                patternAttr_.height.ConvertToPx() / scale_);
//     }
//
//     OH_Drawing_Image *image = OH_Drawing_ImageCreate();
//     OH_Drawing_Brush *brush = OH_Drawing_BrushCreate();
//     OH_Drawing_Bitmap *bitmap = OH_Drawing_BitmapCreate();
//
//     auto *matrix = OH_Drawing_MatrixCreate();
//     if (!patternAttr_.patternTransform.empty()) {
//         LOG(INFO) << "SaveDefinition transform";
//         const auto &transform = attributes_.transform;
//         OH_Drawing_MatrixSetMatrix(matrix, transform[0], transform[2], transform[4] * scale_, transform[1],
//                                    transform[3], transform[5] * scale_, 0, 0, 1.0);
//     }
//
//     OH_Drawing_BitmapFormat cFormat{COLOR_FORMAT_RGBA_8888, ALPHA_FORMAT_OPAQUE};
//     constexpr uint32_t width = 200;
//     constexpr uint32_t height = 200;
//     OH_Drawing_BitmapBuild(bitmap, width, height, &cFormat);
//     OH_Drawing_ImageBuildFromBitmap(image, bitmap);
//
//     OH_Drawing_SamplingOptions *options = OH_Drawing_SamplingOptionsCreate(FILTER_MODE_LINEAR, MIPMAP_MODE_LINEAR);
//     OH_Drawing_ShaderEffect *effect = OH_Drawing_ShaderEffectCreateImageShader(image, REPEAT, REPEAT, options, matrix);
//     OH_Drawing_BrushSetShaderEffect(brush, effect);
//     OH_Drawing_CanvasAttachBrush(newCanvas, brush);
//     OH_Drawing_CanvasBind(newCanvas, bitmap);
//     OH_Drawing_CanvasDrawBackground(newCanvas, brush);
//
//     if (patternAttr_.patternUnits || patternAttr_.patternContentUnits) {
//         LOG(INFO) << "SaveDefinition patternContentUnits";
//         OH_Drawing_Rect *rect = OH_Drawing_RectCreate(50, 100, 500, 500);
//         OH_Drawing_CanvasDrawRect(newCanvas, rect);
//         OH_Drawing_RectDestroy(rect);
//     }
//
//     OH_Drawing_CanvasDestroy(newCanvas);
//     OH_Drawing_ShaderEffectDestroy(effect);
//     OH_Drawing_MatrixDestroy(matrix);
//     OH_Drawing_SamplingOptionsDestroy(options);
//     OH_Drawing_BrushDestroy(brush);
//     OH_Drawing_ImageDestroy(image);
// }

const Pattern &SvgPattern::GetPattern() const { return patternAttr_.pattern; }

void SvgPattern::setPatternX(Dimension x) { 
    patternAttr_.pattern.setPatternX(x); 
}

void SvgPattern::setPatternY(Dimension y) { 
    patternAttr_.pattern.setPatternY(y);
}

void SvgPattern::setHeight(Dimension height) {
    patternAttr_.pattern.setHeight(height); 
}

void SvgPattern::setWidth(Dimension width) { 
    patternAttr_.pattern.setWidth(width); 
}

void SvgPattern::setPatternContentUnits(int patternContentUnits) {
    patternAttr_.pattern.setPatternContentUnits(patternContentUnits); 
}

void SvgPattern::setPatternUnits(int patternUnits) { 
    patternAttr_.pattern.setPatternUnits(patternUnits);
}

void SvgPattern::setTransform(int patternTransform) { 
    patternAttr_.pattern.setTransform(patternTransform);
}

void SvgPattern::setViewBox(Rect viewBox) { 
    patternAttr_.pattern.setViewBox(viewBox); 
}

void SvgPattern::setImage(OH_Drawing_Image* image) { patternAttr_.pattern.setImage(image); }
} // namespace rnoh