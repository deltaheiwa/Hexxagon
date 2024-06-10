#ifndef HEXAGON_PAWN_H
#define HEXAGON_PAWN_H

namespace Hexxagon {
    class Pawn {
    public:
        enum PawnAlignment {
            RUBY,
            PEARL
        };
        Pawn();
        Pawn(PawnAlignment alignment);

        auto getAlignment() const -> PawnAlignment;

        void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    private:
        PawnAlignment alignment;

    };
}

#endif //HEXAGON_PAWN_H
