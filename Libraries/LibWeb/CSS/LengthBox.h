/*
 * Copyright (c) 2018-2020, Andreas Kling <andreas@ladybird.org>
 * Copyright (c) 2025, Sam Atkins <sam@ladybird.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/RefPtr.h>
#include <AK/Variant.h>
#include <LibWeb/CSS/PercentageOr.h>

namespace Web::CSS {

class AnchorStyleValue;

class LengthBox {
public:
    class Side {
    public:
        Side();
        Side(LengthPercentageOrAuto resolved_value);
        ~Side();

        static Side from_anchor(RefPtr<AnchorStyleValue const> anchor);

        Side& operator=(LengthPercentageOrAuto resolved_value);
        Side& operator=(LengthPercentage resolved_value) { return operator=(LengthPercentageOrAuto { move(resolved_value) }); }
        Side& operator=(Length resolved_value) { return operator=(LengthPercentageOrAuto { move(resolved_value) }); }
        Side& operator=(Percentage resolved_value) { return operator=(LengthPercentageOrAuto { move(resolved_value) }); }

        bool is_auto() const { return resolved_value().is_auto(); }
        bool is_length() const { return resolved_value().is_length(); }
        bool is_percentage() const { return resolved_value().is_percentage(); }
        bool is_calculated() const { return resolved_value().is_calculated(); }
        bool contains_percentage() const { return resolved_value().contains_percentage(); }

        LengthPercentage const& length_percentage() const { return resolved_value().length_percentage(); }
        Length const& length() const { return resolved_value().length(); }
        Percentage const& percentage() const { return resolved_value().percentage(); }
        NonnullRefPtr<CalculatedStyleValue const> const& calculated() const { return resolved_value().calculated(); }

        LengthOrAuto resolved_or_auto(Layout::Node const& layout_node, CSSPixels reference_value) const { return resolved_value().resolved_or_auto(layout_node, reference_value); }
        CSSPixels to_px_or_zero(Layout::Node const& layout_node, CSSPixels reference_value) const { return resolved_value().to_px_or_zero(layout_node, reference_value); }

        void serialize(StringBuilder& builder, SerializationMode mode) const { resolved_value().serialize(builder, mode); }
        String to_string(SerializationMode mode) const { return resolved_value().to_string(mode); }

        LengthPercentageOrAuto const& resolved_value() const;
        AnchorStyleValue const* anchor() const;
        operator LengthPercentageOrAuto const&() const { return resolved_value(); }

        bool operator==(Side const&) const = default;

    private:
        explicit Side(RefPtr<AnchorStyleValue const> anchor);

        Variant<LengthPercentageOrAuto, RefPtr<AnchorStyleValue const>> m_value;
    };

    LengthBox();
    LengthBox(Side top, Side right, Side bottom, Side left);
    ~LengthBox();

    Side& top() { return m_top; }
    Side& right() { return m_right; }
    Side& bottom() { return m_bottom; }
    Side& left() { return m_left; }
    Side const& top() const { return m_top; }
    Side const& right() const { return m_right; }
    Side const& bottom() const { return m_bottom; }
    Side const& left() const { return m_left; }

    bool operator==(LengthBox const&) const = default;

private:
    Side m_top;
    Side m_right;
    Side m_bottom;
    Side m_left;
};

}
