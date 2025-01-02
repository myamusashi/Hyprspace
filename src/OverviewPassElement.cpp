#include "OverviewPassElement.hpp"
#include "src/render/OpenGL.hpp"

CRenderModif::CRenderModif(const CRenderModif::SModifData& data_) : data(data_) {
    ;
}

void CRenderModif::draw(const CRegion& damage) {
    if (data.renderModif.has_value())
        g_pHyprOpenGL->m_RenderData.renderModif = *data.renderModif;
}

CRenderRect::CRenderRect(const CRenderRect::SRectData& data_) : data(data_) {
    ;
}

void CRenderRect::draw(const CRegion& damage) {
    if (data.color.a == 1.F || !data.blur)
        g_pHyprOpenGL->renderRect(&data.box, data.color, data.round);
    else
        g_pHyprOpenGL->renderRectWithBlur(&data.box, data.color, data.round, data.blurA, data.xray);
}

bool CRenderRect::needsLiveBlur() {
    return data.color.a < 1.F && !data.xray && data.blur;
}

bool CRenderRect::needsPrecomputeBlur() {
    return data.color.a < 1.F && data.xray && data.blur;
}

std::optional<CBox> CRenderRect::boundingBox() {
    return data.box.expand(-data.round);
}

CRegion CRenderRect::opaqueRegion() {
    return data.color.a >= 1.F ? *boundingBox() : CRegion{};
}

CRenderBorder::CRenderBorder(const CRenderBorder::SBorderData& data_) : data(data_) {
    ;
}

void CRenderBorder::draw(const CRegion& damage) {
    if (data.hasGrad2)
        g_pHyprOpenGL->renderBorder(&data.box, data.grad1, data.grad2, data.lerp, data.round, data.borderSize, data.a, data.outerRound);
    else
        g_pHyprOpenGL->renderBorder(&data.box, data.grad1, data.round, data.borderSize, data.a, data.outerRound);
}
