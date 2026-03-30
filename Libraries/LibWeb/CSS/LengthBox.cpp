/*
 * Copyright (c) 2018-2020, Andreas Kling <andreas@ladybird.org>
 * Copyright (c) 2022, Ben Wiederhake <BenWiederhake.GitHub@gmx.de>
 * Copyright (c) 2025, Sam Atkins <sam@ladybird.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "LengthBox.h"
#include <LibWeb/CSS/StyleValues/AnchorStyleValue.h>

namespace Web::CSS {

static LengthPercentageOrAuto const& auto_length_percentage_or_auto()
{
    static LengthPercentageOrAuto auto_value = LengthPercentageOrAuto::make_auto();
    return auto_value;
}

LengthBox::Side::Side()
    : m_value(LengthPercentageOrAuto::make_auto())
{
}

LengthBox::Side::Side(LengthPercentageOrAuto resolved_value)
    : m_value(move(resolved_value))
{
}

LengthBox::Side::Side(RefPtr<AnchorStyleValue const> anchor)
    : m_value(move(anchor))
{
}

LengthBox::Side::~Side() = default;

LengthBox::Side LengthBox::Side::from_anchor(RefPtr<AnchorStyleValue const> anchor)
{
    VERIFY(anchor);
    return Side(move(anchor));
}

LengthBox::Side& LengthBox::Side::operator=(LengthPercentageOrAuto resolved_value)
{
    m_value = move(resolved_value);
    return *this;
}

LengthPercentageOrAuto const& LengthBox::Side::resolved_value() const
{
    if (auto const* resolved_value = m_value.get_pointer<LengthPercentageOrAuto>())
        return *resolved_value;
    return auto_length_percentage_or_auto();
}

AnchorStyleValue const* LengthBox::Side::anchor() const
{
    if (auto const* anchor = m_value.get_pointer<RefPtr<AnchorStyleValue const>>())
        return anchor->ptr();
    return nullptr;
}

LengthBox::LengthBox()
    : m_top(LengthPercentageOrAuto::make_auto())
    , m_right(LengthPercentageOrAuto::make_auto())
    , m_bottom(LengthPercentageOrAuto::make_auto())
    , m_left(LengthPercentageOrAuto::make_auto())
{
}

LengthBox::LengthBox(Side top, Side right, Side bottom, Side left)
    : m_top(move(top))
    , m_right(move(right))
    , m_bottom(move(bottom))
    , m_left(move(left))
{
}

LengthBox::~LengthBox() = default;

}
