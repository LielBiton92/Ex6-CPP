// #include <stdexcept>
#include "League.hpp"
const int NUM_OF_TEAMS = 20;

League::League()
{
    this->sc = NULL;
}
League::~League()
{
    for (unsigned int i = 0; i < this->sc->get_games().size(); i++)
    {
        delete this->sc->get_games()[i];
    }
    delete this->sc;
    for (unsigned int i = 0; i < this->getTeams().size(); i++)
    {
        delete this->getTeams()[i];
    }
}

Team *League::add_random_team()
{
    unsigned int i = 1;
    unsigned int j = 0;
    std::string to_add = "Barcelona";
    while (j < this->getTeams().size())
    {
        to_add = "Barcelona" + std::to_string(i);
        if (this->getTeams()[j]->getname() == to_add)
        {
            i++;
            j = 0;
        }
        j++;
    }
    double random_talent = ((double)rand() / (RAND_MAX)) + 1;
    Team *randomTeam = new Team(to_add, random_talent);
    return randomTeam;
}

std::vector<Team *> &League::getTeams() { return this->Teams; }

void League::addTeam(Team *t)
{
    this->Teams.push_back(t);
    if (this->Teams.size() > NUM_OF_TEAMS)
    {
        throw("max teams is 20");
    }
}

void League::startLeague()
{
    while (this->getTeams().size() < NUM_OF_TEAMS)
    {

        this->addTeam(add_random_team());
    }
    this->sc = new Schedule(this->getTeams());
}

void League::scoreboard(int num)
{
    for (unsigned int i = 0; i < this->getTeams().size(); i++)
    {
        std::cout << *this->getTeams()[i] << std::endl;
    }
    std::cout << "*********************************" << std::endl;
    std::vector<Team *> temp;
    for (unsigned int i = 0; i < this->getTeams().size(); i++)
    {
        temp.push_back(this->getTeams()[i]);
    }
    std::vector<Team *> res;
    for (unsigned int i = 0; i < this->getTeams().size(); i++)
    {
        Team *t = find_max(temp);
        res.push_back(find_max(temp));
        League::remove(temp, t->getname());
    }
    for (unsigned int i = 0; i < res.size(); i++)
    {
        std::cout << i + 1 << "." << *res[i] << std::endl;
        if (i == num - 1)
        {
            break;
        }
    }
}
void League::scoreboard()
{
    this->scoreboard(this->getTeams().size());
}

Team *League::find_max(std::vector<Team *> teams)
{
    unsigned int i = 0;
    Team *ans = teams[0];
    for (i = 1; i < teams.size(); i++)
    {
        if (*teams[i] > *ans)
        {
            // std::cout << "teams[i] wins : "<< teams[i]->get_wins() << "  ans wins : "<< ans->get_wins()<<std::endl;
            ans = teams[i];
        }
        else if (*teams[i] == *ans)
        {
            if (teams[i]->get_total_points() - teams[i]->get_Points() > ans->get_total_points() - ans->get_Points())
            {
                ans = teams[i];
            }
        }
    }
    // std::cout << " ans  "<< ans->get_wins()<< std::endl;
    return ans;
}

void League::remove(std::vector<Team *> &teams, std::string &name)
{
    unsigned int j = 0;
    for (unsigned int i = 0; i < teams.size(); i++)
    {
        if (teams[i]->getname() == name)
        {
            j = i;
        }
    }
    teams.erase(teams.begin() + j);
    // std::cout<<"size " << teams.size()<<std::endl;
}

void League::BestWS()
{
    Team *BestWS = this->getTeams()[0];
    for (unsigned int i = 0; i < this->getTeams().size(); i++)
    {
        if (this->getTeams()[i]->get_LongestWS() >= BestWS->get_LongestWS())
        {
            BestWS = this->getTeams()[i];
        }
    }
    std::cout << "Best Win Streak is " << BestWS->get_LongestWS() << " by " << BestWS->getname() << std::endl;
}

void League::BestLS()
{
    Team *BestLS = this->getTeams()[0];
    for (unsigned int i = 1; i < this->getTeams().size(); i++)
    {
        if (this->getTeams()[i]->get_LongestLS() >= BestLS->get_LongestLS())
        {
            BestLS = this->getTeams()[i];
        }
    }
    std::cout << "Best loss Streak is " << BestLS->get_LongestWS() << "  by " << BestLS->getname() << std::endl;
}

void League::statisticScore()
{
    int j = 0;
    for (unsigned int i = 1; i < this->getTeams().size(); i++)
    {
        if (this->getTeams()[i]->get_total_points() - this->getTeams()[i]->get_Points() > 0)
        {
            j++;
        }
    }
    std::cout << j << "Teams " << std::endl;
}

void League::HighestScore()
{
    Game *high = this->sc->get_games()[0];
    for (unsigned int i = 1; i < this->sc->get_games().size(); i++)
    {
        if (this->sc->get_games()[i]->get_total_points_of_game() > high->get_total_points_of_game())
        {
            high = this->sc->get_games()[i];
        }
    }
    std::cout << "highest score : " << high->get_total_points_of_game() << " game result :" << high->get_home_score() << " - " << high->get_out_score() << std::endl;
}

void League::LowestScore()
{
    Game *low = this->sc->get_games()[0];
    for (unsigned int i = 1; i < this->sc->get_games().size(); i++)
    {
        if (this->sc->get_games()[i]->get_total_points_of_game() < low->get_total_points_of_game())
        {
            low = this->sc->get_games()[i];
        }
    }
    std::cout << "lowest score : " << low->get_total_points_of_game() << " game result :" << low->get_home_score() << " - " << low->get_out_score() << std::endl;
}

void League::statistic(int num)
{

    this->scoreboard(num);
    this->BestWS();
    this->BestLS();
    this->statisticScore();
    this->HighestScore();
    this->LowestScore();
}

Team::Team(std::string &name, double talent)
{
    
    this->name = name;
    if(this->name.empty()){
        throw ("name cannot be empty");
    }
    this->LS = 0;
    this->WS = 0;
    this->LongestWS = 0;
    this->LongestLS = 0;
    this->points = 0;
    this->totalpoints = 0;
    this->wins = 0;
    this->loss = 0;
    if (talent < 0)
    {
        throw("talent cannot be positive");
    }
    else if(talent > 1){
        throw("talent cannot be greater then 1");
    }
    this->talent = talent;
}
// Team::~Team() {
// }

unsigned int Team::get_Points() const { return this->points; }
std::string &Team::getname() { return this->name; }
unsigned int Team::get_total_points() const { return this->totalpoints; }
void Team::add_to_total_points(unsigned int score) { this->totalpoints += score; }
void Team::add_to_points(unsigned int score) { this->points += score; }
void Team::increaseWS()
{
    this->WS++;
    this->LS = 0;
    if (this->WS >= this->LongestWS)
    {
        this->LongestWS = this->WS;
    }
}
void Team::increaseLS()
{
    this->LS++;
    this->WS = 0;
    if (this->LS >= this->LongestLS)
    {
        this->LongestLS = this->LS;
    }
}
double Team::get_talent() const { return this->talent; }

unsigned int Team::get_wins() const { return this->wins; }
void Team::increasewin() { this->wins++; }
void Team::increaseloss() { this->loss++; }
void Team::print_stats() const
{
    std::cout << " Total wins " << this->wins << std::endl;
    std::cout << " Total loss " << this->loss << std::endl;
    std::cout << " Total points " << this->totalpoints << std::endl;
    std::cout << " Total own " << this->points << std::endl;
}

unsigned int Team::get_loss() const { return this->loss; }

bool Team::operator>(const Team &team1) const
{
    bool ans = false;
    if (this->wins > team1.wins)
    {
        ans = true;
    }
    return ans;
}

bool Team::operator==(const Team &team1) const
{
    bool ans = false;
    if (this->wins == team1.wins)
    {
        ans = true;
    }
    return ans;
}
unsigned int Team::get_LongestWS() const { return this->LongestWS; }
unsigned int Team::get_LongestLS() const { return this->LongestLS; }

std::ostream &operator<<(std::ostream &out, Team &t)
{
    out << "Team name: " << t.getname() << " ,wins: " << t.get_wins() << " ,loss: " << t.get_loss() << " ,total points: " << t.get_total_points() << " ,given points: " << t.get_Points() << " ,clean points: " << (int)t.get_total_points() - (int)t.get_Points();
    return out;
}

const int EXP_HOME = 70;
const int EXP_OUT = 65;
const int VAR = 5;
const int MAX_POINTS = 100;
const int MIN_HOME_POINTS = 55;
const int MIN_OUT_POINTS = 50;

const double MULT_TALENT = 10;

Game::Game(Team *Home, Team *Out)
{
            if(Home==Out){
                throw("same team");
            }
    this->OutTeam = Out;
    this->Home = Home;
    this->total_points_of_game = 0;
    this->homeScore = 0;
    this->outScore = 0;
    this->ScoreGame();
}
// Game::~Game(){}

double Game::get_home_score() const { return this->homeScore; }
double Game::get_out_score() const { return this->outScore; }
int Game::get_total_points_of_game() const { return this->total_points_of_game; }

void Game::ScoreGame()
{
    std::random_device rd{};
    std::mt19937 gen{rd()};

    std::normal_distribution<> Homed{EXP_HOME, VAR};
    std::normal_distribution<> Outd{EXP_OUT, VAR};

    while (homeScore < MIN_HOME_POINTS || homeScore > MAX_POINTS)
    {
        this->homeScore = (int)std::round(Homed(gen));
    }

    while (outScore < MIN_OUT_POINTS || outScore > MAX_POINTS)
    {
        this->outScore = (int)std::round(Outd(gen));
    }

    // std::cout << this->OutTeam->get_talent()<<std::endl;

    int homebonus = (int)(MULT_TALENT * this->Home->get_talent());
    this->homeScore += homebonus;
    if (this->homeScore > 100)
    {
        this->homeScore = 100;
    }
    // std::cout << "home : "<<homeScore <<std::endl;

    int outbonus = (int)(MULT_TALENT * this->OutTeam->get_talent());
    this->outScore += outbonus;
    if (this->outScore > 100)
    {
        this->outScore = 100;
    }
    // std::cout << "Out : "<<outScore<<std::endl;

    this->total_points_of_game = homeScore + outScore;

    this->Home->add_to_total_points(homeScore);
    this->Home->add_to_points(outScore);
    this->OutTeam->add_to_total_points(outScore);
    this->OutTeam->add_to_points(homeScore);
    if (homeScore >= outScore)
    {
        this->Home->increasewin();
        this->Home->increaseWS();
        this->OutTeam->increaseloss();
        this->OutTeam->increaseLS();
    }
    else
    {
        this->OutTeam->increasewin();
        this->OutTeam->increaseWS();
        this->Home->increaseloss();
        this->Home->increaseLS();
    }
}

const int HALF_GAMES = 10;
// Schedule::~Schedule(){}
Schedule::Schedule(std::vector<Team *> &sched)
{
    this->sche = sched;
    unsigned int v = 0;
    for (unsigned int i = 0; i < sche.size() - 1; i++)
    {
        unsigned int j = 0;
        unsigned int k = sche.size() - 1;
        while (j < HALF_GAMES)
        {
            // std::cout << "round num "<< i << " ";
            // std::cout << "Team 1 : " << this->sche.at(j)->getname() << " Team2" <<this->sche.at(k)->getname()<<std::endl;
            Game *g = new Game(this->sche.at(j), this->sche.at(k));
            this->games.push_back(g);
            // std::cout << " game number "<< v++ <<std::endl;
            j++;
            k--;
        }
        this->sche.insert(this->sche.begin() + 1, *(this->sche.erase(this->sche.end() - 1)));
    }
    for (unsigned int i = 0; i < sche.size() - 1; i++)
    {
        unsigned int j = 0;
        unsigned int k = sche.size() - 1;
        while (j < HALF_GAMES)
        {
            // std::cout << "round num "<< i <<" ";
            // std::cout << "Team 1 : " << this->sche.at(k)->getname() << " Team2" <<this->sche.at(j)->getname()<<std::endl;
            Game *g = new Game(this->sche.at(j), this->sche.at(k));
            this->games.push_back(g);
            // std::cout << " game number "<< v++ <<std::endl;
            j++;
            k--;
        }
        this->sche.insert(this->sche.begin() + 1, *(this->sche.erase(this->sche.end() - 1)));
    }
}
std::vector<Game *> Schedule::get_games() { return this->games; }
