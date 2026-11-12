#include "Bot.h"

#include "Utils.h"
#include "Round.h"
#include "../template/Deck.h"

PlayerTurn Bot::AskPlayerForTurn(Card* topCard)
{
    const bool canPlayerMatchCard = CanPlayerMatchCard(topCard);
    if (canPlayerMatchCard)
        return PlayerTurn::PLACE;
    return PlayerTurn::DRAW;
}

PlayerTurnResult Bot::HandlePlayerTurn(Round* round)
{
    const PlayerTurnResult turnResult = PlayerTurnResult::PASS;
    switch (AskPlayerForTurn(round->GetDiscardPile()->PeekTopCard()))
    {
        case PlayerTurn::DRAW:
        {
            // Draw card(s) until
            Card* drawnCard = nullptr;
            while (drawnCard == nullptr || !drawnCard->DoesCardMatch(round->GetDiscardPile()->PeekTopCard()))
            {
                // If the draw deck is empty, refill it using the discard pile
                if (round->GetCardDeck()->IsEmpty())
                    round->RefillDeck();
                drawnCard = round->GetCardDeck()->GetTopCard();
                if (drawnCard == nullptr)
                    continue;
                AddCard(drawnCard);
                std::cout << "Drew card: " << drawnCard->ToString() << "\n";
            }
            // Once bot draws card, get them to place it
            // Take and place card onto discard pile. Will check if player wins
            HandlePlacingCard(round, drawnCard);
            break;
        }
        case PlayerTurn::PLACE:
        {
            Card* cardToPlace = nullptr;
            // See if the bot has an 8 to place
            const int eightCardIndex = FindCard(8);
            if (eightCardIndex != -1)
                cardToPlace = PeekCard(eightCardIndex);
            // Otherwise, get the matching cards and pick a random one to place
            else
            {
                std::vector<Card*> matchableCards = GetMatchableCards(round->GetDiscardPile()->PeekTopCard());
                std::cout << "Matchable cards: ";
                Utils::PrintCards(matchableCards, true, 1);
                const int cardToPlaceIndex = Utils::RandRange(0, static_cast<int>(matchableCards.size()) - 1);
                cardToPlace = matchableCards[cardToPlaceIndex];
            }
            // Take and place card onto discard pile. Will check if player wins and handle the type of card
            HandlePlacingCard(round, cardToPlace);
            break;
        }
        default:
            break;
    }

    return turnResult;
}

PlayerPlaceCardResult Bot::HandlePlacingCard(Round* round, Card* card)
{
    // Take and place card onto discard pile
    if (!round->DiscardCard(this, card))
    {
        std::cout << "[ERROR] Failed to discard card";
        if (card != nullptr)
            std::cout << ": " << card->ToString();
        std::cout << "!\n";
        return PlayerPlaceCardResult::FAILED;
    }
    // Check if player's hand is empty (they win!)
    if (GetHandSize() == 0)
    {
        round->UpdateRoundState(RoundState::FINISHED); // Exit game while loop
        round->OnRoundFinished(this); // This player won!
        return PlayerPlaceCardResult::WON;
    }
    // Check if the card placed was an 8. If so, randomly pick a suit to set it to
    if (card->GetRank() == 8)
    {
        const int newSuitOption = Utils::RandRange(0, 3);
        std::cout << "An eight was played! Pick the next suit ([1] Clubs, [2] Diamonds, [3] Hearts, [4] Spades): " <<
            newSuitOption << "\n";
        card->SetSuit(Utils::GetCardSuitFromOption(newSuitOption));
        std::cout << "Suit picked: " << card->GetSuit() << "\n";
    }
    return PlayerPlaceCardResult::PLACED;
}
