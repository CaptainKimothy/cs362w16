void villageCard(int currentPlayer,struct gameState *state,int handPos){
    //+1 Card
    drawCard(currentPlayer, state);
			
    //+2 Actions
    state->numActions = state->numActions + 2;//numBuys
			
    //discard played card from hand
    discardCard(handPos, currentPlayer, state, 0);
    return 0;
}
///////////////////////////////////////////////////
		
void baronCard(int currentPlayer,struct gameState *state,choice1){
    state->numBuys++;//Increase buys by 1!
     
    if (choice1 > 0){//Boolean true or going to discard an estate
	    int p = 0;//Iterator for hand!
	    int card_not_discarded = 1;//Flag for discard set!

        while(card_not_discarded){
	        if (state->hand[currentPlayer][p] == estate){//Found an estate card!
	            state->coins += 4;//Add 4 coins to the amount of coins
	            state->discard[currentPlayer][state->discardCount[currentPlayer]] = state->hand[currentPlayer][p];
	            state->discardCount[currentPlayer]++;
	    
                for (p < state->handCount[currentPlayer]; p++){
	                state->hand[currentPlayer][p] = state->hand[currentPlayer][p+1];
	            }
	            state->hand[currentPlayer][state->handCount[currentPlayer]] = -1;
	            state->handCount[currentPlayer]--;
	            card_not_discarded = 0;//Exit the loop
	        }
	        else if (p > state->handCount[currentPlayer]){//if handCount is greater than 1 but no estate in hand
	            if(DEBUG) {
	                printf("No estate cards in your hand, invalid choice\n");
	                printf("Must gain an estate if there are any\n");
	            }
	            if (supplyCount(estate, state) > 0){
	                gainCard(estate, state, 0, currentPlayer);
	                state->supplyCount[estate]--;//Decrement estates	      
	            }
	            card_not_discarded = 0;//Exit the loop
	        }		    
	        else{
	            p++;//Next card
	        }
	    }
    }		    
    else{//if player opts to gain a estate card
	    if (supplyCount(estate, state) > 0){
	        gainCard(estate, state, 0, currentPlayer);//Gain an estate
	        state->supplyCount[estate]--;//Decrement Estates
	        
	    }
    }
    if (supplyCount(estate, state) == 0){
        isGameOver(state);
    }
}	    

