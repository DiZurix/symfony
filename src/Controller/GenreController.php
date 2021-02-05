<?php

namespace App\Controller;

use Symfony\Bundle\FrameworkBundle\Controller\AbstractController;
use Symfony\Component\HttpFoundation\Response;
use Symfony\Component\Routing\Annotation\Route;
use Doctrine\ORM\EntityManagerInterface;
use Symfony\Component\HttpFoundation\Request;
use App\Entity\Genre;
use Symfony\Component\HttpFoundation\Session\Session;

class GenreController extends AbstractController
{
    /**
     * @Route("/formGenre", name="formGenre")
     */
    public function index(): Response
    {
        return $this->render('genre/index.html.twig', [
            'controller_name' => '',
        ]);
    }

    /**
     * @Route("/insertGenre", name="insertGenre")
     */
    public function insertGenre(Request $request, EntityManagerInterface $manager): Response
    {
        $Genre = new Genre();
        $Genre->setType($request->request->get('genre'));

        $manager->persist($Genre);
        $manager->flush();

        return $this->render('genre/index.html.twig', [
            'controller_name' => 'Un genre a été ajouté',
        ]);
    } 
}
