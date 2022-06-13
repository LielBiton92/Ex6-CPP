#include "doctest.h"
#include "sources/League.hpp"

TEST_CASE("Game"){
    std::string TeamHome = "Barca";
    std::string TeamOut = "RealMadrid";
    Team *Home = new Team(TeamHome ,0.9 );
    Team *Out = new Team(TeamOut , 0.1);
    Game *g = new Game(Home , Out);
    CHECK(Home->get_total_points()==g->get_home_score());
    CHECK(Out->get_total_points()==g->get_out_score());
    CHECK(g->get_home_score()>50);
    CHECK(g->get_out_score()>55);
    CHECK(g->get_home_score()<100);
    CHECK(g->get_out_score()<100);
    if(g->get_home_score()>=g->get_out_score()){
        CHECK_EQ(Home->get_wins(),1);
    }else{CHECK_EQ(Out->get_wins(),1);}
    CHECK_THROWS(Game *g2 = new Game(Home , Home));
}

TEST_CASE("Team"){
    std::string name="";
    std::string name2= "Barca";
    CHECK_THROWS(Team *t = new Team(name,0.5));
    CHECK_THROWS(Team *t = new Team(name2,-1));
    CHECK_THROWS(Team *t = new Team(name2,2));
    CHECK_NOTHROW(Team *t2 = new Team(name2 , 0.6));
    Team *t3 = new Team(name2 , 0.8);
    t3->increasewin();
    CHECK_EQ(t3->get_wins(),1);

}

TEST_CASE("League"){

}

