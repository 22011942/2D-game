# 2D Terrain Generation Showcase

Hello I would like to say that this is my first project, and the original idea was quite ambitious but that's okay. I originally wanted ot make a 2D game similar to Terraria but i had eventually got bogged down with the porject and lost interest, i know I had made many mistakes but at the same tyime it was a huge learning process as i had never done anything like it before. 

I would say this project has helped me to greatly improve my skills and has reinvigorated me to try again with a new project and set realistic goals. It was the first time I had ever maintained a code base that large and utilized many different tools like Cmake and SFML.

I would say next time I would come up with a plan and create realistic goals which I could accomplish in a realistic time frame. 

### What we have:

The features that I have learnt and implemented through the process:

- Unique Terrain generation using Perlin noise.
- Collision
- Breaking blocks
- Performance improvements.

There are many more features but I believe they are minor when comparted to these main features.

#### Unique Terrain generation:

For the unique terrain generation I had used a multi noise system using Continentalness, Erosion, Peaks and Valleys, Temperature and Humidity, all these noise values would dictate the biome and would also dictate the given height to the terrain. I also utilized a density noise where it would go over the already generated terrain and if the value was a negative in the specified x, y coordinates it would become air, that would allow me to create very unique terrian:

![[Pasted image 20250215203853.png]]
![[Pasted image 20250215203946.png]]
![[Pasted image 20250215204222.png]]
![[Pasted image 20250215204118.png]]

As you can see there cant be many different environments, and yes the generation does have some faults but it was all a learning experience.

#### Collision

For collision I had used AABB collision detection as its one of the simplest forms of collision detection systems. But if I had checked each blocks position relative to the character it would cause a very big performance issue. What I did was only store blocks which were exposed to air in the collision system to reduce performance costs.

![[Collision showcase.gif]]

The main issue I have with collision is that when moving at quite enough speeds it cause the player to clip out of the map.
#### Breaking blocks

This system was quite hard to implement properly and it still causes issues from time to time. But my idea was when a block is removed all the blocks around it which weren't exposed to air must now become collider blocks. It sounds straight forward but for me it was quite challenging to implement.

![[Block breaking showcase.gif]]

The main issue is that when I remove the already existing collider blocks it does not seem to remove them. And another huge issue is when breaking blocks sometimes a segmentation fault occurs and it crashes.

#### Performance improvements

I had made a Chunk based system for rendering blocks so that only what's around the player will be rendered. Here I have an example of its speed with 15 chunks rendering around the player it may not look fast but the entire game is only running on a single thread.

![[Rendering speed showcase.gif]]


