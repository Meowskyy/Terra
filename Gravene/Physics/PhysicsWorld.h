class PhysicsWorld {
    private:
    
    public:
        virtual ~PhysicsWorld() = default;
        virtual void Update() = 0;
};