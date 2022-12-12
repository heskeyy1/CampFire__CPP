struct PARTICLE
{	
	glm::vec3 speed;
    glm::vec3 location;  
    int Left_time;
};

class Particles_sys
{
private:
    vector<PARTICLE>P_particles;
public:
    void InitParticles_sys(int particles_num, glm::vec3 Particles_location_zero)
    {
        for(int i=0;i<particles_num;i++)
        {
            PARTICLE Particles_new;
            Particles_new.location = Particles_location_zero;
            Particles_new.Left_time = 100+ rand()%101;

            this->P_particles.push_back(Particles_new);
        }
    }


    void set_Left_Time(int index,int Left_time)
    {
        this->P_particles[index].Left_time = Left_time;
    }
	
    void P_left_time_decrease(int index)
    {
        this->P_particles[index].Left_time--;
    }



	    int get_Particle_Num()
    {
        return this->P_particles.size();
    }
    void changelocation(int index)
    {
        this->P_particles[index].location += this->P_particles[index].speed;
    }


	void setlocation(int index, glm::vec3 Particles_location_zero)
    {
        this->P_particles[index].location = Particles_location_zero;
    }
	
    void setspeed(int index, glm::vec3 speed)
    {
        this->P_particles[index].speed = speed;
    }



    

    int Particle_left_time(int index)
    {
        return this->P_particles[index].Left_time;
    }

    glm::vec3 getParticlelocation(int index)
    {
        return this->P_particles[index].location;
    }
};
