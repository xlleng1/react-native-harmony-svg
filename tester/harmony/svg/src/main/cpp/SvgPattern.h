#pragma once

#include <string>
#include "SvgQuote.h"
#include "utils/SvgAttributesParser.h"

namespace rnoh {

class SvgPattern : public SvgQuote {

public:
    SvgPattern();
    ~SvgPattern() = default;
    
    virtual void OnDrawTraversedBefore(OH_Drawing_Canvas *canvas) override;
    virtual void OnDrawTraversedAfter(OH_Drawing_Canvas *canvas) override;
    void SaveDefinition(OH_Drawing_Canvas *canvas);
    void ConcatMatrix(OH_Drawing_Canvas *canvas);
    const Pattern &GetPattern() const;

    void setPatternX(Dimension x);

    void setPatternY(Dimension y);

    void setHeight(Dimension height);

    void setWidth(Dimension width);

    void setPatternUnits(int patternUnits);

    void setPatternContentUnits(int patternContentUnits);

    void setTransform(int patternTransform);

    void setViewBox(Rect viewBox);

    void setImage(OH_Drawing_Image *image);

private:
    SvgPatternAttribute patternAttr_;
    double scale_ = 3.25010318;
  };
}