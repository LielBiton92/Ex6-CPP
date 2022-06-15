#include "stdio.h"
#include "vector"
#include <string>
#include <iostream>
#include <cmath>
#include <random>
class Team;
class Schedule;

class League{
    private:
        std::vector<Team*> Teams;
        Schedule *sc;

    public:
        League();
        // League(const League &L);
        // League& operator=(const League &L);
        // League& operator=(League && Other)noexcept; 
        // League(League && Other)noexcept;
        ~League();


        std::vector<Team*>&getTeams();
        Schedule *get_sc();
        void addTeam(Team *t);
        void startLeague();
        void scoreboard(int num );
        void scoreboard();
        static Team* find_max(std::vector<Team*> teams);
        static void remove(std::vector<Team*>&teams ,std::string &name);
        Team *add_random_team();
        void statistic(int num);
        void BestWS();
        void BestLS();
        void statisticScore();
        void HighestScore();
        void LowestScore();
};

class Team {
    private:
        std::string name;
        double talent;
        unsigned int totalpoints;
        unsigned int points;
        unsigned int WS;
        unsigned int LS;
        unsigned int wins;
        unsigned int loss;
        unsigned int LongestWS;
        unsigned int LongestLS;

    public:
        Team(std::string &name ,  double talent);
        // ~Team();
        unsigned int get_Points()const;
        std::string &getname();
        unsigned int get_total_points()const;
        void add_to_total_points(unsigned int score);
        void add_to_points(unsigned int score);
        void increaseWS();
        void increaseLS();
        double get_talent()const;
        unsigned int get_wins()const;
        unsigned int get_loss()const;
        void increasewin();
        void increaseloss();
        void print_stats()const;
        bool operator>(const Team &team1)const;
        bool operator==(const Team &team1)const;
        friend std::ostream& operator<<(std::ostream &out,  Team &t);
        unsigned int get_LongestWS()const;
        unsigned int get_LongestLS()const;
        


        

};

class Game{
    private:
        Team *Home;
        Team *OutTeam;
        unsigned int total_points_of_game;
        unsigned int homeScore;
        unsigned int outScore;
        

    public:
        double get_home_score()const;
        double get_out_score()const;
        unsigned int get_total_points_of_game()const;


        Game(Team *Home , Team *Out);
        // ~Game();
        void ScoreGame();


};

class Schedule{ 
    private:
        std::vector<Team*> sche;
        std::vector<Game*>games;
    public:
        Schedule(std::vector<Team*>&sched);
        // ~Schedule();
        std::vector<Game*>get_games();
};

